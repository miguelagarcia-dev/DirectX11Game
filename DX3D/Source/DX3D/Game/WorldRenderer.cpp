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
#include <DX3D/Component/CubeComponent.h>
#include <DX3D/Math/Vec3.h>
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

	const Vertex vertexList[] =
	{
		{{-0.5f,-0.5f,-0.5f}, {1,0,0,1}},
		{{-0.5f, 0.5f,-0.5f}, {0,1,0,1}},
		{{ 0.5f, 0.5f,-0.5f}, {0,0,1,1}},
		{{ 0.5f,-0.5f,-0.5f}, {1,0,1,1}},
		//the triangles are traced reflectivly which is why the color are mirroed. clockwise rule
		{{ 0.5f,-0.5f, 0.5f}, {1,0,1,1}},
		{{ 0.5f, 0.5f, 0.5f}, {0,0,1,1}},
		{{-0.5f, 0.5f, 0.5f}, {0,1,0,1}},
		{{-0.5f,-0.5f, 0.5f}, {1,0,0,1}}
	};

	const ui32 indexList[] =
	{	//clockwise

		0,1,2,  2,3,0, //first and 2nd triangle
		4,5,6,  6,7,4, //back face
		1,6,5,  5,2,1, //top face
		7,0,3,  3,4,7, //bottom face
		3,2,5,  5,4,3, //right face
		7,6,1,  1,0,7 //left face
	};

	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex) });
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });
}

dx3d::WorldRenderer::~WorldRenderer() {}

//Update happens before clearAndSetBackBuffer so we get   update ->set pipeline -> set buffers -> draw.
void dx3d::WorldRenderer::render(const World& world, SwapChain& swapChain, f32 deltaTime)
{
	auto size = swapChain.getSize();  // orthographic camera setup
	auto aspect = static_cast<f32>(size.width) / size.height;

	auto unitsPerScreenHeight = 5.0f; //world - space height to 2 units(from - 1 to + 1)
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;

	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(size);

	auto numComponents = 0u;
	auto components = world.getComponents<CubeComponent>(numComponents);
	ConstantData data{};

	for (auto i : std::views::iota(0u, numComponents))
	{
		auto component = components[i];
		auto& transform = component->getGameObject().getTransform();

		data = ConstantData
		{
			transform.getWorldMatrix(),
			Mat4x4::orthoLH(viewWidth, viewHeight, -10.0f, 10.0f)
		};

		auto& cb = *m_cb;
		context.updateConstantBuffer(cb, &data);
		context.setVertexBuffer(*m_vb);
		context.setConstantBuffer(cb);
		context.setIndexBuffer(*m_ib);
		context.drawIndexedTriangleList(m_ib->getIndexListSize(), 0u, 0u);
	}

	m_graphicsDevice.executeCommandList(context);
	swapChain.present();
}

//D3D11's default front-face is clockwise so rotateX * rotateY * rotateZ is applield right to left