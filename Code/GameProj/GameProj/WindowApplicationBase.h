#pragma once

using Size1D = int;

struct Size2D
{
	Size1D Weight;
	Size1D Height;
};

//窗体程序基类
//应继承自此类并重写虚函数后使用
class WindowApplicationBase
{
public:
	//使用实例进行初始化
	WindowApplicationBase(HINSTANCE instance);
	//析构
	virtual ~WindowApplicationBase();


public:
	//获取程序实例
	HINSTANCE GetApplicationInstance() const;
	//获取窗体句柄
	HWND GetWindowHandler() const;

	//运行程序
	virtual int RunApplication();
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

	//自定义消息处理回调函数
	virtual LRESULT MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//初始化主窗体
	bool InitializeMainWindow();

	//窗体活动暂停
	virtual void Pause();
	//窗体活动恢复
	virtual void Resume();
	//窗口化窗体
	virtual void Windowize();
	//最小化窗体
	virtual void Minimize();
	//最大化窗体
	virtual void Maximize();

protected:
	HINSTANCE mApplicationInstance;		//程序实例
	HWND			mMainWIndowHandler;		//窗体句柄
	Size2D			mWindowSize;						//输入
};

