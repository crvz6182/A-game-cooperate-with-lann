#pragma once
#include <sstream>
#include "TimeUtility.h"
#include "String.h"
#include "IStringPerformable.h"

class TimeFormatter :public IStringPerformable {
public:
	TimeFormatter(TimePeriodInSecond second = 0, TimePeriodInMinute minute = 0, TimePeriodInHour hour = 0);
	~TimeFormatter();
	virtual String ToString() const override;
private:
	TimePeriodInSecond mSecond;
	TimePeriodInMinute mMinute;
	TimePeriodInHour mHour;
};