#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>
using namespace dx3d; 

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{

	////creating a scope to test error catching, 
	//{
	//	SwapChainPtr sc{};

	//	{
	//		auto sys = std::make_shared<RenderSystem>(RenderSystemDesc{ m_logger }); // turned to share 
	//		sc = sys->createSwapChain({});   //after commenting oujt 
	//	}

	//}


	// create a new render system and assign it to the unique pointer,
	// this will automatically manage the memory and ensure that it is
	// properly released when the graphics engine is destroyed, 
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{m_logger});

}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

RenderSystem& dx3d::GraphicsEngine::getRenderSystem() const noexcept
{
	return *m_renderSystem; 
}