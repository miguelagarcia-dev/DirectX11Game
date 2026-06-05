#include <DX3D/Graphics/RenderSystem.h> 

dx3d::RenderSystem::RenderSystem()
{

	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{}; 

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // enable debug layer in debug mode, this will provide more detailed error messages and warnings when using the Direct3D API, which can help with debugging and development.
#endif

					 // defualt primiary gpu, custome razsterizer, 
	auto hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, NULL, 0, D3D11_SDK_VERSION, 
		&m_d3dDevice, &featureLevel, &m_d3dContext);
		//	                     virtual gpu double pointer 
	
	if (FAILED(hr)) //failed throw this cool catcher "FAILED" 
	{
		throw std::runtime_error("Dirext3d11 intialization failed");
	}


}



dx3d::RenderSystem::~RenderSystem()
{
//	// Properly clean up DirectX resources to avoid "Live Object" warnings
//	if (m_d3dContext)
//	{
//		// Clear all bindings to ensure resources are properly released
//		m_d3dContext->ClearState();
//		m_d3dContext->Flush();
//	}
//
//	// ComPtr will automatically release references, but explicitly nulling ensures clean shutdown
//	m_d3dContext.Reset();
//	m_d3dDevice.Reset();
//
}
