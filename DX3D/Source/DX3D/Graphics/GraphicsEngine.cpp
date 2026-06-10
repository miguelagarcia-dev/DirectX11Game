#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h> 
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <fstream>
#include <cmath>

using namespace dx3d; 

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{

	////creating a scope to test error catching, 
	//{
	//	SwapChainPtr sc{};
	//	{
	//		auto sys = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ m_logger }); // turned to share 
	//		sc = sys->createSwapChain({});   //after commenting oujt 
	//	}
	//}
	// create a new render system and assign it to the unique pointer,
	// this will automatically manage the memory and ensure that it is
	// properly released when the graphics engine is destroyed, 
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

	//constexpr allows to evaluate the value at compile time, which helps us get the string size without upping runtime cost
	//R"()" allows to keep everything within dont leave anythig out
	//the SV_postion is a label that tells the gpu what it represents also know as a sementic 
	//you need to represent the retrun type
	//we can set color of the triangle here 
	constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl"; 
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) DX3DLogThrowError("shader file didnt open.");
	std::string shaderFileData{ //this copies everything into the string shaderFileData
		std::istreambuf_iterator<char>(shaderStream), //marks start of the file
		std::istreambuf_iterator<char>() //marks end
	};

	auto shaderSoruceCode = shaderFileData.c_str(); 
	auto shaderSoruceCodeSize = shaderFileData.length(); 

 	auto vs = device.compileShader({ shaderFilePath, shaderSoruceCode, shaderSoruceCodeSize,
		"VSMain", ShaderType::VertexShader});
	auto ps = device.compileShader({ shaderFilePath, shaderSoruceCode, shaderSoruceCodeSize,
		"PSMain", ShaderType::PixelShader}); 
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
	{
		 //clockwise

		//front face
		0,1,2,  //first triangle
		2,3,0,  //second triangle
				//back face
		4,5,6,
		6,7,4,
				//top face
		1,6,5,
		5,2,1,
				//bottom face
		7,0,3,
		3,4,7,
				//right face
		3,2,5,
		5,4,3,
				//left face
		7,6,1,
		1,0,7
	};
	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex)});
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex) });
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });
	m_ib = device.createIndexBuffer({ indexList, std::size(indexList) });

}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice; 
}

//Update happens before clearAndSetBackBuffer so we get   update ->set pipeline -> set buffers -> draw.
void dx3d::GraphicsEngine::render(SwapChain& swapChain, f32 deltaTime)
{
	auto& context = *m_deviceContext;
	auto& cb = *m_cb;

	m_pos += deltaTime * 0.0f;
	m_rot += deltaTime * 0.707f;
	m_scale = std::abs(std::sin(m_rot));

	auto worldMat =
		Mat4x4::scale({ m_scale, m_scale, m_scale }) *
		Mat4x4::rotateX(m_rot) *
		Mat4x4::rotateY(m_rot) *
		Mat4x4::rotateZ(m_rot) *
		Mat4x4::translate({ m_pos, m_pos, 0 });

	// orthographic camera setup
	auto size = swapChain.getSize();
	auto aspect = static_cast<f32>(size.width) / size.height;

	//world - space height to 2 units(from - 1 to + 1)
	auto unitsPerScreenHeight = 2.0f;
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;

	ConstantData data
	{
		worldMat,
		Mat4x4::orthoLH(viewWidth, viewHeight, -10.0f, 10.0f)
	};

	context.updateConstantBuffer(cb, &data);

	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	auto& ib = *m_ib;
	context.setVertexBuffer(vb);
	context.setConstantBuffer(cb);
	context.setIndexBuffer(ib);
	context.drawIndexedTriangleList(ib.getIndexListSize(), 0u, 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}

//D3D11's default front-face is clockwise so rotateX * rotateY * rotateZ is applield right to left