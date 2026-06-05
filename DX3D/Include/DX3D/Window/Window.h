#pragma once
#include <DX3D/Core/Base.h> // we need to include the Base class header file to inherit from it

namespace dx3d 
{
	class Window: public Base  // we are inhereiting for Base now 
	{

	public: 
		//compiler will catch mismatches in function signatures 
		// such as if we accidentally misspelled the function name or 
		// if the function signature does not match the base class, the c
		// ompiler will generate an error, which helps us catch bugs early 
		// in the development process.
		Window(); 
		virtual ~Window() override; 
	
	private:
		void* m_handle{}; // We used this so  it doesnt expose the platform spescfic API 
		
	};

}

	
