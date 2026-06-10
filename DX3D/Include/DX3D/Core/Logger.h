#pragma once
#include <DX3D/Core/Core.h>
#include <format>

namespace dx3d
{
	class Logger final 
	{
		dx3d_disable_copy_and_move(Logger)
	public:
		enum class LogLevel { Error = 0, Warning, Info };

		explicit Logger(LogLevel logLevel = LogLevel::Error);  // constructor
		~Logger();
	
		
		// explicit- allows for no accidental conversions through implicit means for this single aurgment constructor 
		template<typename... Args>
		void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
		{
			auto str = std::format(fmt, std::forward<Args>(args)...);
			_log(level, str.c_str());
		}

	private:
		void _log(LogLevel level, const char* message);

	//copy move assigment operators should not be called, rule of zero 
	private:
		LogLevel m_logLevel = LogLevel::Error; 

	};

}
	
// use \ to altert that theres more macros
//spaces after the back slash matter

#define DX3DLog(logger, type, message,...)\
    logger.log((type), {message} __VA_OPT__(,) __VA_ARGS__);

#define DX3DLogThrow(logger, exception, type, message, ...)\
{\
DX3DLog(logger,type,message, __VA_ARGS__);\
throw exception(message);\
}

//updated them with new logger defs in logger.h
#define DX3DLogInfo(message,...)\
    DX3DLog(getLogger(), Logger::LogLevel::Info, message, __VA_ARGS__)

#define DX3DLogWarning(message,...)\
    DX3DLog(getLogger(), Logger::LogLevel::Warning, message, __VA_ARGS__)

#define DX3DLogError(message,...)\
    DX3DLog(getLogger(), Logger::LogLevel::Error, message, __VA_ARGS__)

#define DX3DLogThrowError(message,...)\
    DX3DLogThrow(getLogger(), std::runtime_error, Logger::LogLevel::Error, message, __VA_ARGS__)

#define DX3DLogThrowInvalidArg(message,...)\
    DX3DLogThrow(getLogger(), std::invalid_argument, Logger::LogLevel::Error, message, __VA_ARGS__)