#pragma once
#include <DX3D/Game/Component.h>
#include <DX3D/Graphics/GraphicsDevice.h>

namespace dx3d
{
	class VertexBuffer;
	class IndexBuffer;
	class Texture;
	class MeshComponent : public Component 
	{
		dx3d_typeid(MeshComponent)
	public: 
		explicit MeshComponent(const MeshComponentDesc& desc);
					
		void setMesh(const VertexBufferDesc& vDesc, const IndexBufferDesc& iDesc);
		const RefPtr<VertexBuffer>& getVertexBuffer() const; //getters
		const RefPtr<IndexBuffer>& getIndexBuffer() const;
		
		void setTexture(RefPtr<Texture> texture);
		const RefPtr<Texture>& getTexture() const;
	private: 
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
		RefPtr<Texture> m_texture{};
		RefPtr<VertexBuffer> m_vertexBuffer{};
		RefPtr<IndexBuffer> m_indexBuffer{};
	};
} 
