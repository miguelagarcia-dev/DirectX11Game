#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>


namespace dx3d
{

	class Game : public Base
	{

	public: 

		explicit Game(const GameDesc& desc);
		virtual ~Game() override;

		virtual void run() final; //final means that this fuction cannot be overridden or inherinated lets us stop unintentioned extentsions

	private: 
		void onInternalUpdate(); //where we can place the coad that needs to be exucuted each frame 

	private: 
		std::unique_ptr<Logger> m_loggerPtr{};
		// we have to worry about the unique pointer position 
		// the last defined attbuite is the first to be deallocated and vice versa 
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{}; // graphics engine instance, we use a smart pointer to manage the memory and ensure that it is properly released when the game is destroyed,
		// now think about needing to manually delete something and 
		// forgetting, a smart point helps with this since theyre auto 
		std::unique_ptr<Display> m_display{};  // window instance 

		//Window* m_display{};  //old-disaly attrubitued 
		bool m_isRunning{ true }; // this is a flag to control the main game loop, we can set it to false to exit the loop and end the game.}




	};



} 
