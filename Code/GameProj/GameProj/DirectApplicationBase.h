#pragma once
#include "Timer.h"

using Size1D = int;

struct Size2D
{
	Size1D Weight;
	Size1D Height;
};

//使用Direct进行加速渲染的窗体程序基类
//应继承自此类并重写虚函数后使用
class DirectApplicationBase
{
public:
	//使用实例进行初始化
	DirectApplicationBase(HINSTANCE instance);
	//析构
	~DirectApplicationBase();


public:
	//获取程序实例
	HINSTANCE GetApplicationInstance() const;
	//获取窗体句柄
	HWND GetWindowHandler() const;

	//运行程序
	int RunApplication();
	//退出程序
	void Quit();

	/*******************
	以下为虚函数
	纯虚函数必须被重写
	 *******************/

	//初始化窗体
	virtual bool Initialization();

	//当窗体大小被更改时会调用此函数
	virtual void OnResize();
	//每次有效循环会调用此函数
	//更新游戏场景
	//timeElapsed: 距离上次调用此函数过去了的时间（秒）
	virtual void Update(TimePointInSecond timeElapsed);
	//每次有效循环会调用此函数
	//绘制图像
	virtual void Draw();
	//自定义消息处理回调函数
	virtual LRESULT MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	//初始化主窗体
	bool InitializeMainWindow();
	//窗体活动暂停
	void Pause();
	//窗体活动恢复
	void Resume();
	//窗口化窗体
	void Windowize();
	//最小化窗体
	void Minimize();
	//最大化窗体
	void Maximize();
protected:
	HINSTANCE mApplicationInstance;		//程序实例
	HWND			mMainWIndowHandler;		//窗体句柄
	Timer			mTimer;								//计时器
	Size2D			mWindowSize;						//输入
};

