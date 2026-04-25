//---------------------------------------------------------------------------

#pragma hdrstop

#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace LogSys
{
    void __fastcall Logger::log(
        Level level, const String& message, const char* func, const char* file, int line)
	{
        std::lock_guard<std::mutex> lock(mutex_);
        logFile_ << "[" << levelToString(level) << "] " << file << ":" << line << " " << func
                 << " - " << message.c_str() << std::endl;
    }

} // namespace LogSys

