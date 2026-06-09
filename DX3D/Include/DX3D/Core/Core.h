#pragma once
#include <stdexcept>
#include <memory> // allows for smart pointeers 

namespace dx3d
{
	//forward declaration of classes in the core module. 
	// used to declare the existentance of calls without needing to provied the full def. 

	class Base;
	class Window;
	class Game; 
	class GraphicsEngine;
	class GraphicsDevice;
	class Logger; 
	class SwapChain; 
	class Display; 
	class DeviceContext; 
	class ShaderBinary;
	class GraphicsPipelineState; //make sure to make allias using share pointe 
	class VertexBuffer;

	using i32 = int; //representing 32 bit int 
	using ui32 = unsigned int; // 
	using f32 = float;
	using d64 = double; 

	//type allias 
	//shared pointer, manenges the life time of a dynamical allocated object using ref counting, different from smart where it dels once out of scope
	using SwapChainPtr = std::shared_ptr<SwapChain>;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>; 
	using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
	using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;


	// this is a new type too 
}