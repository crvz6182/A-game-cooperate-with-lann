#pragma once
#include <fstream>
#include "stdafx.h"
#include "String.h"
#include "TimeFormatter.h"
#include "FileIO.h"
#include "DirectApplicationBase.h"


constexpr char DEBUGLOGPATH[] = "\\tLog\\DebugLog.txt";

enum LogType{
	LOG_DEBUG = 0,
	LOG_EXCEPTIONOPERATION = 1
};

class Log {
public:
	static bool Print(LogType type,const String &content);
	static void RegisterDirectApplication(DirectApplicationBase *app);
private:
	static DirectApplicationBase *mApplication;
};



