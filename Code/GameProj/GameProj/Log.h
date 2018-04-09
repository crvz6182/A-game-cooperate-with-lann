#pragma once
#include <fstream>
#include "stdafx.h"
#include "String.h"
#include "TimeFormatter.h"
#include "FileIO.h"
#include "GameApplication.h"

#define DEBUGLOGPATH "\\tLog\\DebugLog.txt"

class GameApplication;

enum LogType{
	LOG_DEBUG = 0,
	LOG_EXCEPTIONOPERATION = 1
};

class Log {
public:
	static bool Print(LogType type,const String &content);
	static void RegisterDirectApplication(GameApplication *app);
private:
	static GameApplication *mApplication;
};



