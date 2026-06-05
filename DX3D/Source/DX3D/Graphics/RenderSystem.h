#pragma once

#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>


namespace dx3d
{
	class RenderSystem final: public Base
	{
	
	public: 
		RenderSystem();
		virtual ~RenderSystem() override;
	
	private: 
		//device pointer for virtual gpu, 
		//this uses refernece content, meaning theres a counter for how many things are pointer to
		// when its 0 it self dels
		// this is the main interface for creating resources and managing the graphics pipeline, it represents the virtual GPU and is used to create and manage resources such as buffers, textures, shaders, and states.
		
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
	
	};

}
	


