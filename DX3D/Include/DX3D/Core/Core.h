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
}