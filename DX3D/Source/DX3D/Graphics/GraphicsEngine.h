#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d
{
	// we need to use final here because we don't want to allow inheritance from this class,
	// as it is the main class of the engine and should not be extended or modified by users,
	// it should be used as is, and if users want to extend or modify the engine, they should 
	// create their own classes that use the engine as a component, rather than inheriting from it.

	class GraphicsEngine final : public Base 
	{ 
	public:

		//constructor and destructor
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override; // override the destructor to ensure that it is called when the object is destroyed
		

		GraphicsDevice& getGraphicsDevice() noexcept;

		void render(SwapChain& swapChain); 

	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{}; //turned into a shared pointer 
		DeviceContextPtr  m_deviceContext{};
		GraphicsPipelineStatePtr m_pipeline{}; 

	};
}
	
