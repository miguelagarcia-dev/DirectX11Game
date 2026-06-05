
#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>

dx3d::Game::Game()
{

	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	//instead make a smart  pointer to manage the memory automatically and avoid manual deletion,
	m_display = std::make_unique<Window>(); // this creates a new Window object and assigns it to the m_display unique pointer.
	// old- new Window(); 
	//// we create a new Window object and assign it to the m_display pointer.


	//the rule of five? 
	//Window win{};
	//auto w = win; //shallow copy - this just skims of the top to make a copy creating two window objects which  BAD !!

}


dx3d::Game::~Game()
{

	//old-replaced with smart poiter 
	// delete m_display; // using new? always use deletle. this is to not clog the heap with mem leaks 
	// you can also use smart pointers like std::unique_ptr to
	// automatically manage the memory and avoid manual deletion, 
	// but for simplicity we are using raw pointers here.

}


