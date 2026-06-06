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
		
		explicit Logger(LogLevel loglevel = LogLevel::Error); // explicit- allows for no accidental conversions through implicit means for this single aurgment constructor  
		void log(LogLevel level, const char* message) const; // const make sure we dont alter noting 

		//copy move assigment operators should not be called, rule of zero 


	private:

		LogLevel m_logLevel = LogLevel::Error; 

	};
}
	
	

