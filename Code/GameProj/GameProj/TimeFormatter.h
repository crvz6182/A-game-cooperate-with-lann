#pragma once
#include <sstream>
#include "TimeUtility.h"
#include "String.h"
#include "IStringPerformable.h"

class TimeFormatter :public IStringPerformable {
public:
	TimeFormatter(TimePointInSecond second = 0, TimePointInMinute minute = 0, TimePointInHour hour = 0);
	~TimeFormatter();
	virtual String ToString() const override;
private:
	TimePointInSecond mSecond;
	TimePointInMinute mMinute;
	TimePointInHour mHour;
};