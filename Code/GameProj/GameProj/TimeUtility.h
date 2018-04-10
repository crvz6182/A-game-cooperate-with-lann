#pragma once


//以秒计时的时间点
using TimePointInSecond = float;

using TimePeriodInSecond = unsigned int;
//以分计时的时间点
using TimePeriodInMinute = TimePeriodInSecond;
//以时计时的时间点
using TimePeriodInHour = TimePeriodInSecond;
//以Count计时的时间点
using TimePointInCount = time_t;
//以秒计时的时间段
using TimeSlotInSecond = float;
//以Count计时的时间段
using TimeSlotInCount = time_t;