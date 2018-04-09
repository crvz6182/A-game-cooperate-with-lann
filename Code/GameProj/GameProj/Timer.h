#pragma once
#include <time.h>
#include <Windows.h>
#include "TimeUtility.h"




//��ʱ��
class Timer
{
public:
	Timer();
	~Timer();

	//���ü�ʱ��
	void ResetTimer();
	//��ͣ��ʱ��
	void PauseTimer();
	//�ָ���ʱ��
	void ResumeTimer();
	//��ʱ��һ����ÿ֡����
	void Tick();
	//��ȡ����Ч��ʱʱ�����룩
	TimeSlotInSecond GetTotalValidTime() const;
	//��ȡ������Ч��ʱ��ʱ���룩
	TimeSlotInSecond GetDeltaTime() const;
private:
	//��ȡ��ǰʱ��㣨Count��
	TimePointInCount GetCurrentCount();
private:
	TimeSlotInSecond		mSecondsPerCount;			//ÿ��Count��Ӧ������

	TimePointInCount		mStartCount;						//��ʼ��ʱʱ��ʱ���
	TimePointInCount		mPreviousCount;					//�ϴ���Ч��ʱ�õ���ʱ���
	TimePointInCount		mCurrentCount;					//��ǰ��Ч��ʱ�õ���ʱ���
	
	TimePointInCount		mPauseCount;						//�ϴε�����ͣʱ��ʱ���
	
	TimeSlotInCount			mPausedSlotCount;				//һ����ͣ�˶��
	bool								mPausing;							//��ǰ�Ƿ�����ͣ״̬
};

