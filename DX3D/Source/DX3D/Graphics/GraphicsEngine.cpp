#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h> 
#include <DX3D/Math/Vec3.h>
#include <DX3D/Graphics/VertexBuffer.h>

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
	constexpr char shaderSoruceCode[] =
		R"(
float4 VSMain(float3 pos: POSITION): SV_Position
{
return float4(pos.xyz, 1.0);
}
float4 PSMain(): SV_Target
{
return float4(1.0, 1.0, 1.0, 1.0);
}
)"; 
	constexpr char shaderSoruceName[] = "Basic";
	constexpr auto shaderSoruceCodeSize = std::size(shaderSoruceCode); 

	auto vs = device.compileShader({shaderSoruceName, shaderSoruceCode, shaderSoruceCodeSize,
		"VSMain", ShaderType::VertexShader});

	auto ps = device.compileShader({shaderSoruceName, shaderSoruceCode, shaderSoruceCodeSize,
	"PSMain", ShaderType::PixelShader}); 

	m_pipeline = device.createGraphicsPipelineState({ *vs, *ps });

	const Vec3 vertexList[] = 
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	m_vb = device.createVertexBuffer({ vertexList, std::size(vertexList), sizeof(Vec3)});
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice; 
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext; 
	context.clearAndSetBackBuffer(swapChain, { 0,0,0,1 }); // this renders colors 
	context.setGraphicsPipelineState(*m_pipeline);

	context.setViewportSize(swapChain.getSize());

	auto& vb = *m_vb;
	context.setVertexBuffer(vb);
	context.drawTriangleList(vb.getVertexListSize(), 0u);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
