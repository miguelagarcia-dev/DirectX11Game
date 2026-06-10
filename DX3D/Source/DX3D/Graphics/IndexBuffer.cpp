#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/GraphicsUtils.h>

dx3d::IndexBuffer::IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc), m_listSize(desc.indexListSize)
{
    if (!desc.indexList) DX3DLogThrowInvalidArg("No index list provided.");
    if (!desc.indexListSize) DX3DLogThrowInvalidArg("Index list size must be non-zero.");

    D3D11_BUFFER_DESC buffDesc{};
    buffDesc.ByteWidth = desc.indexListSize * sizeof(ui32);
    buffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = desc.indexList;

    DX3DGraphicsLogThrowOnFail(m_device.CreateBuffer(&buffDesc, &initData, &m_buffer),
        "CreateIndexBuffer failed.");
}

dx3d::ui32 dx3d::IndexBuffer::getIndexListSize() const noexcept
{
    return m_listSize;
}
