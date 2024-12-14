#include "Logger.h"

void Logger::Destroy()
{
	if (s_Instance)
	{
		s_Instance->m_Output.flush();
		delete s_Instance;
		s_Instance = nullptr;
	}
}

Logger::Logger(std::ostream& output)
	: m_Output(output)
{
}
