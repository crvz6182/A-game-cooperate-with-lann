#pragma once
#include "WindowApplicationBase.h"
#include "Timer.h"

//使用Direct进行硬件加速渲染的窗体程序基类
//应继承此类并重写纯虚函数后使用
class DirectApplicationBase :
	public WindowApplicationBase
{
public:
	DirectApplicationBase(HINSTANCE hInstance);
	virtual ~DirectApplicationBase();

	//运行程序
	//Direct窗体程序需要维护一个主循环，因此运行函数有所不同
	virtual int RunApplication() override;

	//每次有效循环会调用此函数
	//更新游戏场景
	//timeElapsed: 距离上次调用此函数过去了的时间（秒）
	virtual void Update(TimeSlotInSecond deltaTime);

	//每次有效循环会调用此函数
	//绘制图像
	virtual void Draw();

	//窗体活动暂停
	virtual void Pause() override;

	//窗体活动恢复
	virtual void Resume() override;
private:
	Timer mTimer;				//计时器
};

