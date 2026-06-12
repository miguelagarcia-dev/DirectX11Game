
#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/WorldRenderer.h>
#include <DX3D/Input/InputSystem.h>



dx3d::Game::Game(const GameDesc& desc)
{	
	m_logger = std::make_unique<Logger>(desc.logLevel);

	DX3DLogInfo("DirectX C++ 3D Game");

	m_inputSystem = std::make_unique<InputSystem>(InputSystemDesc{ *m_logger });
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{ *m_logger });

	//instead make a smart  pointer to manage the memory automatically and avoid manual deletion,
	// this creates a new Window object and assigns it to the m_display unique pointer.
	m_display = std::make_unique<Display>(DisplayDesc{ {*m_logger, desc.windowSize}, *m_graphicsDevice });
	
	// old- new Window(); 
	//// we create a new Window object and assign it to the m_display pointer.
	//the rule of five? 
	//Window win{};
	//auto w = win; //shallow copy - this just skims of the top to make a copy creating two window objects which  BAD !!

	m_world = std::make_unique<World>(WorldDesc{ {*m_logger}, GameContext{*m_inputSystem} });
	m_worldRenderer = std::make_unique<WorldRenderer>(WorldRendererDesc{ {*m_logger},*m_graphicsDevice });

	m_inputSystem->setCursorLockArea(m_display->getClientAreaInScreenSpace());

	DX3DLogInfo("Game Initialized");
}

dx3d::InputSystem& dx3d::Game::getInputSystem() noexcept {return *m_inputSystem;}

dx3d::World& dx3d::Game::getWorld() noexcept { return *m_world; }
dx3d::RefPtr<dx3d::GraphicsDevice> dx3d::Game::getGraphicsDevice() noexcept {return m_graphicsDevice; }


dx3d::Game::~Game(){ DX3DLogInfo("Game is shutting down..");
	//old-replaced with smart poiter 
	// delete m_display; // using new? always use deletle. this is to not clog the heap with mem leaks 
	// you can also use smart pointers like std::unique_ptr to
	// automatically manage the memory and avoid manual deletion, 
	// but for simplicity we are using raw pointers here.
}

dx3d::Logger& dx3d::Game::getLogger() noexcept
{
	return *m_logger;
}


void dx3d::Game::onInternalUpdate()
{//this method isnt platform spec so we moved this into here from Win32Game

	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<f32> delta = currentTime - m_previousTime;
	m_previousTime = currentTime;
	auto deltaTime = delta.count();

	m_inputSystem->update();
	onUpdate(deltaTime);

	m_world->update(deltaTime);

	m_worldRenderer->render(*m_world, m_display->getSwapChain(), deltaTime);


}