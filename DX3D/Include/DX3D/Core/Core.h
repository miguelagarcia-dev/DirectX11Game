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
	class RenderSystem;
	class Logger; 
	class SwapChain; 
	class Display; 


	using i32 = int; //representing 32 bit int 
	using ui32 = unsigned int; // 
	using f32 = float;
	using d64 = double; 

	//shared pointer, manenges the life time of a dynamical allocated object using ref counting, different from smart where it dels once out of scope
	using SwapChainPtr = std::shared_ptr<SwapChain>;
	// this is a new type too 
}