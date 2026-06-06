#include <DX3D/Core/Logger.h>
#include <iostream>

dx3d::Logger::Logger(LogLevel loglevel): m_logLevel(loglevel)
{

	std::clog << "Dirext X 3D FPS Game | C++" << "\n"; 

}

void dx3d::Logger::log(LogLevel level, const char* message) const // this is the log function 
{
	auto logLevelToString = [](LogLevel level) {   //we make enum to basically call int's as strings so level x is " string x". 
		switch (level)
		{
		case LogLevel::Info: return "Info";
		case LogLevel::Warning: return "Warning";
		case LogLevel::Error: return "Error";
		default: return "Unkown"; 
		}

		};


	if (level > m_logLevel);
	std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";

}
