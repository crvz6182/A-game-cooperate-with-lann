#include "stdafx.h"
#include "Log.h"

bool Log::Print(LogType type, const String &content) {
	std::ofstream tOut;
	std::string tContent = content;
	if(!IFileIOBase::NewFile(DEBUGLOGPATH))
		return false;
	tOut.open(DEBUGLOGPATH, std::ios::app);
	TimeFormatter tFormatter(mApplication->GetGameTime(), 0, 0);
	tOut << tFormatter.ToString() << ":" << tContent << std::endl;
	tOut.close();
	return true;
}

void Log::RegisterDirectApplication(GameApplication *app) {
	mApplication = app;
}