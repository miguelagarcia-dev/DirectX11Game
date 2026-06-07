#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsLogUtils.h> 

#include <d3d11.h>
#include <wrl.h>


namespace dx3d
{
	struct GraphicsResourceDesc
	{ 
		BaseDesc base; 
		std::shared_ptr<const RenderSystem> renderSystem; //const is used to make sure no motifications can be done 
		ID3D11Device& device;
		IDXGIFactory& factory;
	};
	class GraphicsResource : public Base
	{
	public: 
		explicit GraphicsResource(const GraphicsResourceDesc& desc):
			Base(desc.base),
			m_renderSystem(desc.renderSystem),
			m_device(desc.device),
			m_factory(desc.factory)
		{
		}

	
	protected: //proctected means it can only be used from dervied classes no external access.
		std::shared_ptr<const RenderSystem> m_renderSystem;
		ID3D11Device& m_device; 
		IDXGIFactory& m_factory; 
	};

}