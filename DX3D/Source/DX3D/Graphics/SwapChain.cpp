#include <DX3D/Graphics/SwapChain.h>

//implmetning methods 
//the first constructer is like the big guy with genreal things. when you make a new method you add it to the intitiaze list here.
dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_size(desc.winSize)
{
	// if we passs zero -values this will fail 
	if (!desc.winHandle) DX3DLogThrowInvalidArg(" No win handler provided.");
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	
	dxgiDesc.BufferDesc.Width = std::max(1, desc.winSize.width);  //the surface we render to 
	dxgiDesc.BufferDesc.Height = std::max(1, desc.winSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //4 color channels , unorm are normiazed as 0-1 range in the shader. 
	dxgiDesc.BufferCount = 2; //back buffers, windows dwm handles the front buffer
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 

	dxgiDesc.OutputWindow = static_cast<HWND>(desc.winHandle);
	dxgiDesc.SampleDesc.Count = 1; //sample usage for anti aliasing
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 
	dxgiDesc.Windowed = TRUE; 

	DX3DGraphicsLogThrowOnFail(m_factory.CreateSwapChain(&m_device, &dxgiDesc, &m_swapChain),
		"CreateSwapChain failed."); 

	reloadBuffers();

}

dx3d::Rect dx3d::SwapChain::getSize() const noexcept
{
	return m_size;
}

void dx3d::SwapChain::present(bool vsync)
{
	DX3DGraphicsLogThrowOnFail(m_swapChain->Present(vsync, 0), // this is a vsync and the amount vertical waits. 0 migth cause tearing 
		"Present failed.");  
}

void dx3d::SwapChain::reloadBuffers()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{}; 
	DX3DGraphicsLogThrowOnFail(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)),
		"GetBuffer failed.");
	DX3DGraphicsLogThrowOnFail(m_device.CreateRenderTargetView(buffer.Get(), nullptr, &m_rtv),
		"CreateRenderTargetViewfailed."); 
}

