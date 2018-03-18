#pragma once
#include <time.h>
#include <Windows.h>

//以秒计时的时间点
using TimePointInSecond = float;
//以Count计时的时间点
using TimePointInCount = time_t;
//以秒计时的时间段
using TimeSlotInSecond = float;
//以Count计时的时间段
using TimeSlotInCount = time_t;

//计时器
class Timer
{
public:
	Timer();
	~Timer();

	//重置计时器
	void ResetTimer();
	//暂停计时器
	void PauseTimer();
	//恢复计时器
	void ResumeTimer();
	//计时，一般在每帧调用
	void Tick();
	//获取总有效计时时长（秒）
	TimeSlotInSecond GetTotalValidTime() const;
	//获取两次有效计时的时间差（秒）
	TimeSlotInSecond GetDeltaTime() const;
private:
	//获取当前时间点（Count）
	TimePointInCount GetCurrentCount();
private:
	TimeSlotInSecond		mSecondsPerCount;			//每个Count对应多少秒

	TimePointInCount		mStartCount;						//开始计时时的时间点
	TimePointInCount		mPreviousCount;					//上次有效计时得到的时间点
	TimePointInCount		mCurrentCount;					//当前有效计时得到的时间点
	
	TimePointInCount		mPauseCount;						//上次调用暂停时的时间点
	
	TimeSlotInCount			mPausedSlotCount;				//一共暂停了多久
	bool								mPausing;							//当前是否在暂停状态
};

