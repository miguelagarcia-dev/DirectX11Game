#include <DX3D/Game/WorldRenderer.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Component/MeshComponent.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Component/CameraComponent.h>
#include <fstream>
#include <ranges>

//replacing gameengine to decouple 
dx3d::WorldRenderer::WorldRenderer(const WorldRendererDesc& desc) : Base(desc.base), m_graphicsDevice(desc.engine)
{
	auto& device = m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("Failed to open shader file.");
	std::string shaderFileData{ // this copies everything into the string shaderFileData
		std::istreambuf_iterator<char>(shaderStream), //marks start of the file
		std::istreambuf_iterator<char>() //and end
	};

	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	auto vs = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "VSMain", ShaderType::VertexShader });
	auto ps = device.compileShader({ shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "PSMain", ShaderType::PixelShader });
	auto vsSig = device.createVertexShaderSignature({ vs });
	m_pipeline = device.createGraphicsPipelineState({ *vsSig, *ps });

	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });

	D3D11_SAMPLER_DESC sampDesc{};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	device.m_d3dDevice->CreateSamplerState(&sampDesc, &m_sampler);
}

dx3d::WorldRenderer::~WorldRenderer() {}

//Update happens before clearAndSetBackBuffer so we get   update ->set pipeline -> set buffers -> draw.
void dx3d::WorldRenderer::render(const World& world, SwapChain& swapChain, f32 deltaTime)
{ 
	auto size = swapChain.getSize(); // orthographic camera setup

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(size);

	auto numComponents = 0u;
	ConstantData data{};

	// Pass 1: get view + projection from the first CameraComponent
	{
		auto components = world.getComponents<CameraComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			data.view = component->getViewMatrix();
			component->setViewportSize(size);
			data.proj = component->getProjectionMatrix();
			break;
		}
	}

	// Pass 2: render cubes
	{
		auto components = world.getComponents<MeshComponent>(numComponents);
		for (auto i : std::views::iota(0u, numComponents))
		{
			auto component = components[i];
			auto& transform = component->getGameObject().getTransform();
			data.world = transform.getAffineWorldMatrix();  // getWorldMatrix() → getAffineWorldMatrix()

			auto& cb = *m_cb;
			context.updateConstantBuffer(cb, &data);

			auto& vb = *component->getVertexBuffer();
			auto& ib = *component->getIndexBuffer();
			context.setVertexBuffer(vb);
			context.setConstantBuffer(cb);
			context.setIndexBuffer(ib);

			if (auto& tex = component->getTexture())
				context.setTexture(*tex);

			auto sampler = m_sampler.Get();
			m_deviceContext->m_context->PSSetSamplers(0, 1, &sampler);

			context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);
		}
	}

	m_graphicsDevice.executeCommandList(context);
	swapChain.present();
}

//D3D11's default front-face is clockwise so rotateX * rotateY * rotateZ is applield right to left