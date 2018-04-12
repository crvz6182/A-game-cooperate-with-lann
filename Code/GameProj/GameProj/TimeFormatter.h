#pragma once
#include <sstream>
#include "TimeUtility.h"
#include "String.h"
#include "IStringPerformable.h"

class TimeFormatter :public IStringPerformable {
public:
	TimeFormatter(TimeSpotInSecond second = 0, TimeSpotInMinute minute = 0, TimeSpotInHour hour = 0);
	~TimeFormatter();
	virtual String ToString() const override;
private:
	TimeSpotInSecond mSecond;
	TimeSpotInMinute mMinute;
	TimeSpotInHour mHour;
};