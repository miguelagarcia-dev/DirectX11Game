#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>

dx3d::GraphicsEngine::GraphicsEngine()
{
	// create a new render system and assign it to the unique pointer,
	// this will automatically manage the memory and ensure that it is
	// properly released when the graphics engine is destroyed, 
	m_renderSystem = std::make_unique<RenderSystem>(); 

}

dx3d::GraphicsEngine::~GraphicsEngine()
{


}
