#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>

//these are descriptors expaling what something will have 
namespace dx3d
{
	struct BaseDesc  // grouping dependencies for the base class 
	{

		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base; 
		Rect size{};
	};


	struct DisplayDesc
	{
		WindowDesc window; 
		GraphicsDevice& graphicsDevice;

	};

	struct WorldRendererDesc
	{
		BaseDesc base;
		GraphicsDevice& engine;
	};

	struct GraphicsDeviceDesc
	{
		BaseDesc base; 
	};


	struct SwapChainDesc
	{
		void* winHandle{};
		Rect winSize{}; 

	};

	//defining what type of shader we're passing in 

	enum class ShaderType
	{
		VertexShader = 0, //processes the vertices of the object
		PixelShader  //how the surface should be colored 
	};

	struct ShaderCompileDesc
	{	
		//passing our soruce code to be compoiled 
		const char* shaderSourceName{}; //we use char instead of string because string isnt abi safe - it has the same memmory layout and size across all major compoilers. char is a row pointers
		const void* shaderSourceCode{}; //pointer here acts as a read-only mode 
		size_t shaderSourceCodeSize{};  //size_t is an aggrate choice since we dont know how big the soucre code will be, but know it will be large
		const char* shaderEntryPoint{}; 
		ShaderType shaderType{}; 
	};

	struct BinaryData
	{
		const void* data{};
		size_t dataSize{};
	}; // make methods in the class

	struct GraphicsPipelineStateDesc
	{
		const VertexShaderSignature& vs;
		const ShaderBinary& ps;  //users of the struct would only be able to access in read only by using const
	};

	struct VertexBufferDesc
	{
		const void* vertexList{};
		ui32 vertexListSize{}; //the number of vertices 
		ui32 vertexSize{};
	};

	struct VertexShaderSignatureDesc
	{
		const RefPtr<ShaderBinary>& vsBinary;//we want ownership to be taken by the hlsl filler
	};

//constbuffer Constant buffers (cbuffers) are how the CPU sends small, frequently-updated data (matrices, scalars, colors, time values)
	struct ConstantBufferDesc 
	{
		const void* buffer{};
		ui32 bufferSize{};
	};

	struct IndexBufferDesc
	{
		const ui32* indexList{};
		ui32 indexListSize{};
	};

	struct GameDesc
	{
		Rect windowSize{ 1280,720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error; 
	};

	struct WorldDesc
	{
		BaseDesc base;
	};

	struct GameObjectDesc
	{
		BaseDesc base;
		World& world;
	};

	struct ComponentDesc
	{
		BaseDesc base;
		GameObject& object;
		World& world;
	};

}
