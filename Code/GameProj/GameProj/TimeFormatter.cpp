#include "stdafx.h"
#include "TimeFormatter.h"

TimeFormatter::TimeFormatter(TimeSpotInSecond second, TimeSpotInMinute minute, TimeSpotInHour hour) {
	mSecond = second % 60;
	mMinute = (minute + second / 60) % 60;
	mHour = hour + (minute + second / 60) / 60;
}

TimeFormatter::~TimeFormatter(){

}

String TimeFormatter::ToString() const
{
	std::stringstream stream;
	std::string tContent;
	stream << mHour << "h " << mMinute << "m " << mSecond << "s";
	tContent = stream.str();
	return String(tContent.c_str());
}
