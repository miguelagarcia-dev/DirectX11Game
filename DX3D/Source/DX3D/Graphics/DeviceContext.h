#pragma once
#include <DX3D/Graphics/GraphicsResource.h> 
#include <DX3D/Math/Vec4.h>

namespace dx3d
{

	class DeviceContext final: public GraphicsResource
	{

	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc); //remeber that marking as explicit means not expecting more paramters  
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
		void setVertexBuffer(const VertexBuffer& buffer);
		void setViewportSize(const Rect& size);
		void drawTriangleList(ui32 vertexCount, ui32 startVertexLocation);
		void setConstantBuffer(const ConstantBuffer& buffer);
		void updateConstantBuffer(const ConstantBuffer& buffer, const void* data);
		void setIndexBuffer(const IndexBuffer& buffer);
		void drawIndexedTriangleList(ui32 indexCount, ui32 startVertexIndex, ui32 startIndexLocation);

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class GraphicsDevice; 
	};




}