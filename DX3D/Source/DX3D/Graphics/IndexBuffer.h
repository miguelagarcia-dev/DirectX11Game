#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{

	class IndexBuffer final : public GraphicsResource
	{
    public:
        IndexBuffer(const IndexBufferDesc& desc, const GraphicsResourceDesc& gDesc);
        ui32 getIndexListSize() const noexcept;
    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
        ui32 m_listSize{};

        friend class DeviceContext;
	};


}
