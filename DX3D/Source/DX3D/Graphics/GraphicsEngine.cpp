#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h> 

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
	constexpr char shaderSoruceCode[] =
		R"(
void VSMain()
{
}
void PSMain()
{
}
)"; 
	constexpr char shaderSoruceName[] = "Basic";
	constexpr auto shaderSoruceCodeSize = std::size(shaderSoruceCode); 

	auto vs = device.compileShader({shaderSoruceName, shaderSoruceCode, shaderSoruceCodeSize,
		"VSMain", ShaderType::VertexShader});

	auto ps = device.compileShader({shaderSoruceName, shaderSoruceCode, shaderSoruceCodeSize,
	"PSMain", ShaderType::PixelShader}); 

	m_pipeline = device.createGraphicsPipelineState({ *vs, *ps });

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
	context.clearAndSetBackBuffer(swapChain, { 1,1,0,1 }); // this renders colors 
	context.setGraphicsPipelineState(*m_pipeline);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();

}
