#include <DX3D/Core/Logger.h>
#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel): m_logLevel(logLevel){}

dx3d::Logger::~Logger() {}

void dx3d::Logger::_log(LogLevel level, const char* message)  // this is the log function 
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


	if (level > m_logLevel) return;
	std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";

}
