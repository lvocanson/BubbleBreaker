#include "Logger.h"

Logger::Logger(std::ostream& output)
	: m_Output(output)
{
}

Logger::~Logger()
{
	m_Output.flush();
}
