#ifndef NLOG_HPP
#define NLOG_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "Time.hpp"

class NLog
{
    public:
		static NLog& instance();

        enum LogType
        {
            Error,
            Warning,
            Info,
        };

        static void setLogType(LogType type);
        static void log(std::string const& message);

        friend NLog& operator<<(NLog& log, std::string const& message)
        {
            std::stringstream ss;
            ss << NTime::getTime("[%x][%X]");
            switch (log.mType)
            {
                case NLog::LogType::Error:
                    ss << "[ERROR] : ";
                    break;

                case NLog::LogType::Warning:
                    ss << "[WARNING] : ";
                    break;

                default:
                    ss << "[INFO] : ";
            }
            ss << message;
            std::string str = ss.str();

            if (log.mConsole)
                std::cout << str << std::endl;

            if (log.mFile.is_open())
                log.mFile << str << std::endl;

            log.mType = NLog::LogType::Info;

            return log;
        }

        friend NLog& operator<<(NLog& log, LogType type)
        {
            log.mType = type;
            return log;
        }

        static bool openLog(std::string const& filename);
        static bool isLogOpen();

        static void useConsole(bool use);

	protected:
        NLog();

		static NLog mInstance;

    protected:
        std::ofstream mFile;
        bool mConsole;
        LogType mType;
};

#endif // NLOG_HPP
