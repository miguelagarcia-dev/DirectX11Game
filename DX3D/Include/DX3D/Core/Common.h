#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>

namespace dx3d
{
	struct BaseDesc  // grouping dependencies for the base class 
	{

		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base; 
	};

	struct GraphicsEngineDesc 
	{
		BaseDesc base; 
	};

	struct RenderSystemDesc
	{
		BaseDesc base; 
	};
	struct GameDesc
	{
		Logger::LogLevel logLevel = Logger::LogLevel::Error; 
	};
}
