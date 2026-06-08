#pragma once


namespace dx3d
{
	class Logger final 
	{
	public: 
		enum class LogLevel
		{
			Error = 0, 
			Warning,
			Info 

		};
	
		explicit Logger(LogLevel logLevel = LogLevel::Error); // explicit- allows for no accidental conversions through implicit means for this single aurgment constructor 
		~Logger();

		void log(LogLevel level, const char* message) ; // removed const 06/08 -const make sure we dont alter noting 

	protected:  //deleting copy move operation to not accidently repalce logger intance  
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

	//copy move assigment operators should not be called, rule of zero 
	private:
		LogLevel m_logLevel = LogLevel::Error; 

	};

}
	
	

#define DX3DLog(logger ,type, message)\
logger.log((type), message)

#define DX3DLogThrow(logger, exception, type, message)\
{\
DX3DLog(logger, type, message);\
throw exception(message);\
}
