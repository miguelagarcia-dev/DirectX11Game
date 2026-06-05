#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>


namespace dx3d
{

	class Game : public Base
	{

	public: 

		Game();
		virtual ~Game() override;

		virtual void run() final; //final means that this fuction cannot be overridden or inherinated lets us stop unintentioned extentsions

	private: 
		// now think about needing to manually delete something and 
		// forgetting, a smart point helps with this since theyre auto 
		std::unique_ptr<Window> m_display{};  // window instance 

		//Window* m_display{};  //old-disaly attrubitued 
		bool m_isRunning{ true }; // this is a flag to control the main game loop, we can set it to false to exit the loop and end the game.}

	};



} 
