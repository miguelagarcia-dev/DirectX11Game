#pragma once
#include <stdexcept>
#include <memory> // allows for smart pointeers 

//boilerpalte dupe for deleting constc and ops
#define dx3d_disable_copy_and_move(Class)     \
protected:\
    Class(const Class&) = delete;        \
    Class& operator=(const Class&) = delete; \
    Class(Class&&) = delete;             \
    Class& operator=(Class&&) = delete;

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
	class VertexShaderSignature; 
	class ConstantBuffer;
	class IndexBuffer;

	class World;
	class GameObject;
	class Component;
	class TransformComponent;
	class WorldRenderer;

	using i32 = int; //representing 32 bit int 
	using ui32 = unsigned int; // 
	using f32 = float;
	using d64 = double; 


	//type allias // this is a new type too 
	//shared pointer, manenges the life time of a dynamical allocated object using ref counting, different from smart where it dels once out of scope
	template <typename T> using RefPtr = std::shared_ptr<T>;
	template <typename T> using UniquePtr = std::unique_ptr<T>;

}