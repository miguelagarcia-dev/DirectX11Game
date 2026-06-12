
#include <DX3D/Graphics/Texture.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Component/MeshComponent.h>

dx3d::MeshComponent::MeshComponent(const MeshComponentDesc& desc) :
	Component(desc.base)
{
	m_graphicsDevice = desc.graphicsDevice;

}
void dx3d::MeshComponent::setMesh(const VertexBufferDesc& vDesc, const IndexBufferDesc& iDesc)
{//filling m with a getter
	m_vertexBuffer = m_graphicsDevice->createVertexBuffer(vDesc);
	m_indexBuffer = m_graphicsDevice->createIndexBuffer(iDesc);
}

const dx3d::RefPtr<dx3d::VertexBuffer>& dx3d::MeshComponent::getVertexBuffer() const
{
	return m_vertexBuffer;
}

const dx3d::RefPtr<dx3d::IndexBuffer>& dx3d::MeshComponent::getIndexBuffer() const
{
	return m_indexBuffer;
}

void dx3d::MeshComponent::setTexture(RefPtr<Texture> texture)
{
	m_texture = texture;
}

const dx3d::RefPtr<dx3d::Texture>& dx3d::MeshComponent::getTexture() const
{
	return m_texture;
}
