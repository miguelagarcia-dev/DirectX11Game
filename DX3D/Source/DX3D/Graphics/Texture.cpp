#define STB_IMAGE_IMPLEMENTATION
#include <ThirdParty/stb_image.h>
#include <DX3D/Graphics/Texture.h>



dx3d::Texture::Texture(const TextureDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc)
{
	D3D11_TEXTURE2D_DESC texDesc{};
	texDesc.Width = desc.width;
	texDesc.Height = desc.height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = desc.data;
	initData.SysMemPitch = desc.rowPitch;

	// my texture, get a view into it for the shader
	m_device.CreateTexture2D(&texDesc, &initData, &m_texture);
	m_device.CreateShaderResourceView(m_texture.Get(), nullptr, &m_srv);


}

ID3D11ShaderResourceView* dx3d::Texture::getTexture() const noexcept
{
	return m_srv.Get();
}


