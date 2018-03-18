#include "stdafx.h"
#include "Timer.h"


Timer::Timer():
	mStartCount(0),
	mPreviousCount(0),
	mCurrentCount(0),
	mPauseCount(0),
	mPausedSlotCount(0),
	mPausing(false)
{
	time_t countsPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER *)&countsPerSecond);
	mSecondsPerCount = 1.0f / ((float)countsPerSecond);
}


Timer::~Timer()
{
}

void Timer::ResetTimer()
{
	mStartCount = mPreviousCount = mCurrentCount = GetCurrentCount();
	mPauseCount = 0;
	mPausedSlotCount = 0;
	mPausing = false;
}

void Timer::PauseTimer()
{
	if (mPausing) {
		return;
	}
	mPausing = true;
	mPauseCount = GetCurrentCount();
}

void Timer::ResumeTime()
{
	if (!mPausing) {
		return;
	}
	mPausing = false;
	Tick();
	//������ͣʱ�� = ���λָ���ʱʱ��� - ������ͣ��ʱʱ���
	mPausedSlotCount += mCurrentCount - mPauseCount;
}

void Timer::Tick()
{
	if (mPausing) {
		return;
	}
	mPreviousCount = mCurrentCount;
	mCurrentCount = GetCurrentCount();
}

TimeSlotInSecond Timer::GetTotalValidTime() const
{
	//������ʱ�� = ��ǰʱ��� - ��ʼʱ��� - ��ͣ��ʱ��
	return (mCurrentCount - mStartCount - mPausedSlotCount) * mSecondsPerCount;
}

TimeSlotInSecond Timer::GetDeltaTime() const
{
	return (mCurrentCount - mPreviousCount) * mSecondsPerCount;
}

TimePointInCount Timer::GetCurrentCount()
{
	TimePointInCount currentCount;
	QueryPerformanceCounter((LARGE_INTEGER *)&currentCount);
	return currentCount;
}
