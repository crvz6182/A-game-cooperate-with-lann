#include "stdafx.h"
#include "Log.h"

DirectApplicationBase * Log::mApplication = nullptr;

bool Log::Print(LogType type, const String &content) {
	if (mApplication == nullptr)
		return false;
	std::ofstream tOut;
	std::string tContent = content;
	if(!IFileIOBase::NewFile(DEBUGLOGPATH))
		return false;
	tOut.open(DEBUGLOGPATH, std::ios::app);
	TimeFormatter tFormatter((TimePeriodInSecond)mApplication->GetGameTime(), 0, 0);
	tOut << tFormatter.ToString() << ":" << tContent << std::endl;
	tOut.close();
	return true;
}

void Log::RegisterDirectApplication(DirectApplicationBase *app) {
	mApplication = app;
}