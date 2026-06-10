#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h> 
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>
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
	{	//clockwise drawing
		{ {-0.5f, -0.5f, 0.0f}, {1,0,0,1} }, //first point
		{ {-0.5f, 0.5f, 0.0f }, {0,1,0,1} },
		{ { 0.5f, 0.5f, 0.0f }, {0,0,1,1} },
		//2ndtriangle
		{ {0.5f, 0.5f, 0.0f} , { 0,0,1,1 } },
		{ {0.5f, -0.5f, 0.0f}, { 1,0,1,1 } },
		{{-0.5f, -0.5f, 0.0f}, { 1,0,0,1 } }  //same as first point
	};


	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vertex)});
	m_cb = device.createConstantBuffer({ {}, sizeof(ConstantData) });

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
	// Matrix multiplication is not commutative.
	//s0 in that order S * R * T
	m_pos += deltaTime * 0.5f;
	m_rot += deltaTime * 3.14f;
	m_scale = std::abs(std::sin(m_rot));

	DX3DLogInfo("Pos: X:{} Y:{}", m_pos, m_pos);
	DX3DLogInfo("Rot: Z:{}", m_rot);
	DX3DLogInfo("Scale: {}", m_scale);

	auto worldMat =
		Mat4x4::scale({ m_scale, m_scale, m_scale }) *
		Mat4x4::rotateZ(m_rot) *
		Mat4x4::translate({ m_pos, m_pos, 0 });

	ConstantData data
	{
		worldMat
	};

	context.updateConstantBuffer(cb, &data);

	context.clearAndSetBackBuffer(swapChain, { 0.27f, 0.39f, 0.55f, 1.0f });
	context.setGraphicsPipelineState(*m_pipeline);
	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.setConstantBuffer(cb);
	context.drawTriangleList(vb.getVertexListSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
