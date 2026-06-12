#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>
#include <chrono>

namespace dx3d
{

	class Game
	{
		dx3d_disable_copy_and_move(Game)

	public: 
		explicit Game(const GameDesc& desc);
		virtual ~Game();

		//final means that this fuction cannot be overridden or inherinated lets us stop unintentioned extentsions
		virtual World& getWorld() noexcept final;
		virtual Logger& getLogger() noexcept final; //accesors
		virtual RefPtr<GraphicsDevice> getGraphicsDevice() noexcept final; //addign a refernece to device for meshcomponet
		virtual void run() final; 

		virtual InputSystem& getInputSystem() noexcept final;

	protected:
		virtual void onCreate() {};
		virtual void onUpdate(f32 deltaTime) {};

	private: 
		void onInternalUpdate(); //where we can place the coad that needs to be exucuted each frame 

	private: 
		UniquePtr<Logger> m_logger{};
		
		// we have to worry about the unique pointer position 
		// the last defined attbuite is the first to be deallocated and vice versa 
		// we use a smart pointer to manage the memory and ensure that it is properly released when the game is destroyed,
		RefPtr<GraphicsDevice>  m_graphicsDevice{};
		UniquePtr<WorldRenderer> m_worldRenderer{};
		
		// now think about needing to manually delete something and 
		// forgetting, a smart point helps with this since theyre auto 
		UniquePtr<Display> m_display{};  // window instance 
		UniquePtr<World> m_world{};
		UniquePtr<InputSystem> m_inputSystem{};

		//Window* m_display{};  //old-disaly attrubitued 
		bool m_isRunning{ true }; // this is a flag to control the main game loop, we can set it to false to exit the loop and end the game.}	
		std::chrono::steady_clock::time_point m_previousTime{};
	};

} 
