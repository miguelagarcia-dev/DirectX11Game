#include <DX3D/Graphics/GraphicsDevice.h> 
#include <DX3D/Graphics/GraphicsLogUtils.h> 
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>

using namespace dx3d; //using namespace in header files need caution as collisions can be created 

dx3d::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc) : Base(desc.base)
{

	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{}; 

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // enable debug layer in debug mode, this will provide more detailed error messages and warnings when using the Direct3D API, which can help with debugging and development.
#endif
											 // defualt primiary gpu, custome razsterizer, 
	DX3DGraphicsLogThrowOnFail(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, 
		NULL, 0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext),
		 "Dirext3d11 intialization failed.");           

	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)) ,
		"QueryInterface failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogThrowOnFail( m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactory.");
	// these will enable swap chain usage. 
 
	//if (FAILED(hr)) //failed throw this cool catcher "FAILED" 
	//{
	//	//updated to new error handling through macro 
	//	//getLogger().log(Logger::LogLevel::Error, );
	//	//throw std::runtime_error("Dirext3d11 intialization failed");
	//}
}

dx3d::GraphicsDevice::~GraphicsDevice()
{
}



SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc)
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{}; 
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList failed.");

	m_d3dContext->ExecuteCommandList(list.Get(), false);  // this sends to the gpu 

}

GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{	
	// { {} } we initalized braces to the logger since its part of the base desc structure     
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get() };  //share from this allows us to not direct pass in the pooitner 
}
