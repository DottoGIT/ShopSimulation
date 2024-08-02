#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

enum class LogPriority
{
    DebugPriority,
    InfoPriority,
    WarningPriority,
    ErrorPriority
};

class Log
{
public:
    Log(const LogPriority& priority_, const std::string& content_)
        :priority(priority_), content(content_) {}
    std::string GetContent() const {return content;}
    LogPriority GetPriority() const {return priority;}
private:
    LogPriority priority;
    std::string content;
};

class Logger
{
public:
    static void SetPriority(const LogPriority& priority_);
    static std::vector<Log> GetLogs();
    static void Debug(const std::string& message);
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
private:
    inline static LogPriority priority = LogPriority::InfoPriority;
    inline static std::vector<Log> logs;
};


#endif // LOGGER_H
