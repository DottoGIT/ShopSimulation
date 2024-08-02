#include "logger.h"

void Logger::SetPriority(const LogPriority& priority_)
{
    priority = priority_;
}

std::vector<Log> Logger::GetLogs()
{
    std::vector<Log> retVec;
    std::copy_if(logs.begin(), logs.end(), std::back_inserter(retVec), [](const Log& log){
        return log.GetPriority() >= priority;
    });
    return retVec;
}

void Logger::Debug(const std::string& message)
{
    logs.push_back(Log(LogPriority::DebugPriority, "Debug: " + message));
}

void Logger::Info(const std::string& message)
{
    logs.push_back(Log(LogPriority::InfoPriority, "Info: " + message));
}

void Logger::Warning(const std::string& message)
{
    logs.push_back(Log(LogPriority::WarningPriority, "Warning: " + message));
}

void Logger::Error(const std::string& message)
{
    logs.push_back(Log(LogPriority::ErrorPriority, "Error: " + message));
}
