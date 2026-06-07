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
		void log(LogLevel level, const char* message) const; // const make sure we dont alter noting 

		//copy move assigment operators should not be called, rule of zero 
	private:
		LogLevel m_logLevel = LogLevel::Error; 

	};

//define is a preprocess directive that tells the compioler to replace the instance of a name before compilation begins
// use \ to altert that theres more macros
//spaces after the back slash matter


#define DX3DLogInfo(message)\
	getLogger().log((Logger::LogLevel::Info), message);

#define DX3DLogWarning(message)\
	getLogger().log((Logger::LogLevel::Warning), message);


#define DX3DLogError(message)\
	getLogger().log((Logger::LogLevel::Error), message);

#define DX3DLogErrorAndThrow(message)\
	{\
	DX3DLogError(message);\
	throw std::runtime_error(message);\
	}
}
	
	

