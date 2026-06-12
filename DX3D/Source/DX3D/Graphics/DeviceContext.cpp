#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/Texture.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc)
{
	DX3DGraphicsLogThrowOnFail(m_device.CreateDeferredContext(0, &m_context), 
		"CreateDeferredContext failed.") 
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{


	f32 fColor[] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_rtv.Get();
	m_context->ClearRenderTargetView(rtv, fColor);//since the swap chain class has a method thats private we cant access it so we can use a friend class. formally bypassing that locked method
	m_context->OMSetRenderTargets(1, &rtv, nullptr);

}

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	m_context->IASetInputLayout(pipeline.m_layout.Get());
	m_context->VSSetShader(pipeline.m_vs.Get(), nullptr, 0);
	m_context->PSSetShader(pipeline.m_ps.Get(), nullptr, 0);

}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
	auto stride = buffer.m_vertexSize;
	auto buf = buffer.m_buffer.Get();
	auto offset = 0u; //u declares its an unsiged int
	m_context->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<f32>(size.width); 
	vp.Height = static_cast<f32>(size.height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0;  //clippping plane paramters 


	m_context->RSSetViewports(1, &vp); 
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	//how it assembles data into triangle primatives and how to connect verties to foarm shapes 
	//every group of 3 vertieces will be treated as an indepentdent triangle 
	
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->Draw(vertexCount, startVertexLocation);
			//start with vertex we ask 
}

//setConstantBuffer binds to both VSSetConstantBuffers and PSSetConstantBuffers at slot 0.
void dx3d::DeviceContext::setConstantBuffer(const ConstantBuffer& buffer)
{
	auto buf = buffer.m_buffer.Get();
	m_context->VSSetConstantBuffers(0, 1, &buf);
	m_context->PSSetConstantBuffers(0, 1, &buf);
}

//"I don't care about the old contents, give me a fresh region if the GPU is still using it." This avoids a CPU/GPU sync stall every frame.
void dx3d::DeviceContext::updateConstantBuffer(const ConstantBuffer& buffer, const void* data)
{
	if (!data) DX3DLogThrowInvalidArg("Null data pointer passed to updateConstantBuffer.");

	auto buf = buffer.m_buffer.Get();
	D3D11_MAPPED_SUBRESOURCE mapped{};
	DX3DGraphicsLogThrowOnFail(m_context->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped),
		"ID3D11DeviceContext::Map failed.");
	std::memcpy(mapped.pData, data, buffer.m_size);
	m_context->Unmap(buf, 0);
}
//we need to find verts before drawing them
void dx3d::DeviceContext::setIndexBuffer(const IndexBuffer& buffer)
{
	m_context->IASetIndexBuffer(buffer.m_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

//same as the regular draw trangle just with buffer
void dx3d::DeviceContext::drawIndexedTriangleList(ui32 indexCount, ui32 startVertexIndex, ui32 startIndexLocation)
{
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_context->DrawIndexed(indexCount, startIndexLocation, startVertexIndex);
}

void dx3d::DeviceContext::setTexture(const Texture& texture)
{
	auto srv = texture.getTexture();
	m_context->PSSetShaderResources(0, 1, &srv);
}

