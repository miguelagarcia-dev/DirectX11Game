
#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc) : 
	Base({ *std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger)
{	

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});

	//instead make a smart  pointer to manage the memory automatically and avoid manual deletion,
	m_display = std::make_unique<Display>(DisplayDesc{ {m_logger, desc.windowSize},m_graphicsEngine->getGraphicsDevice()});  // this creates a new Window object and assigns it to the m_display unique pointer.
	// old- new Window(); 
	//// we create a new Window object and assign it to the m_display pointer.
	//the rule of five? 
	//Window win{};
	//auto w = win; //shallow copy - this just skims of the top to make a copy creating two window objects which  BAD !!
	
	DX3DLogInfo("Game Initialized");

}

dx3d::Game::~Game()
{
	DX3DLogInfo("Game is shutting down..");

	//old-replaced with smart poiter 
	// delete m_display; // using new? always use deletle. this is to not clog the heap with mem leaks 
	// you can also use smart pointers like std::unique_ptr to
	// automatically manage the memory and avoid manual deletion, 
	// but for simplicity we are using raw pointers here.

}



void dx3d::Game::onInternalUpdate()
{		//this method isnt platform spec so we moved this into here from Win32Game

	m_graphicsEngine->render(m_display->getSwapChain());

}