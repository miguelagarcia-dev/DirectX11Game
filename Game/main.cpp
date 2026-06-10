#include "MainGame.h"


int main()
{
	try
	{
		MainGame game({ {1280,720}, dx3d::Logger::LogLevel::Info });
		game.run();
	}

	//try
	//{
	//	// we create an instance of the Game class, which will 
	//	// initialize the game and create a window for us.
	//	dx3d::Game game({ {1280, 720},dx3d::Logger::LogLevel::Info });

	//	// we call the run method of the Game class, which will start the
	//	// main game loop and keep the game running until we decide to exit it.
	//	game.run();
	//}

	catch(const std::runtime_error&)
	{
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument&)
	{
		return EXIT_FAILURE;
	}
	catch(const std::exception&)
	{
		return EXIT_FAILURE;
	}
	catch(...) //catch all handler for any others that we dont know might show 
	{
		return EXIT_FAILURE;
	}
	

	return EXIT_SUCCESS;
}

	