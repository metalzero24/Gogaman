#pragma once

#include "pch.h"
#include "Gogaman/Core.h"

namespace Gogaman
{
	enum class LogLevel
	{
		Trace, Info, Warning, Error
	};

	class GOGAMAN_API Logger
	{
	public:
		Logger(std::string name);
		~Logger();

		void Log(const LogLevel level, const char *format, ...);

		void SetLogLevel(LogLevel level) { m_LogLevel = level; }
		inline LogLevel GetLogLevel() { return m_LogLevel; }
	private:
		std::string m_LogName;
		LogLevel m_LogLevel = LogLevel::Trace;
		std::ostringstream m_OutputStringStream;
	};
}