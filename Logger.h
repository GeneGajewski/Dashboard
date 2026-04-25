//---------------------------------------------------------------------------

#ifndef LoggerH
#define LoggerH
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <mutex>

namespace LogSys
{
	enum Level
	{
		logDEBUG,
		logINFO,
		logWARNING,
		logERROR,
		logFATAL
	};

	class Logger
	{
	  public:
		static Logger& instance()
		{
			static Logger logger("app.log");
			return logger;
		}

		void __fastcall log(
			Level level, const String& message, const char* func, const char* file, const int line);
	  private:
		Logger(const std::string& filename) : logFile_(filename, std::ios::app) {}
		std::wofstream logFile_;
		std::mutex mutex_;

		const wchar_t* levelToString(Level l)
		{
			switch (l)
			{
				case logDEBUG:
					return L"DEBUG";
				case logINFO:
					return L"INFO";
				case logWARNING:
					return L"WARN";
				case logERROR:
					return L"ERROR";
				case logFATAL:
					return L"FATAL";
			}
			return L"UNKNOWN";
		}
	};

} // namespace LogSys

#define Log(_level, _msg) Logger::instance().log(_level, _msg, __FUNC__, __FILE__, __LINE__)


#endif

