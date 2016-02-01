#include "Log.hpp"

NLog NLog::mInstance;

NLog& NLog::instance()
{
	return mInstance;
}

void NLog::setLogType(LogType type)
{
    mInstance << type;
}

void NLog::log(std::string const& message)
{
    mInstance << message;
}

NLog::NLog() : mFile(), mConsole(true), mType(NLog::LogType::Info)
{
    openLog("Assets/Data/log.dat");
}

bool NLog::openLog(std::string const& filename)
{
    mInstance.mFile.open(filename,std::ios::app);
    return mInstance.mFile.is_open();
}

bool NLog::isLogOpen()
{
    return mInstance.mFile.is_open();
}

void NLog::useConsole(bool use)
{
    mInstance.mConsole = use;
}
