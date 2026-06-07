#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/RenderSystem.h>


dx3d::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
	m_swapChain = desc.renderSystem.createSwapChain({ m_handle, m_size }); 
}
