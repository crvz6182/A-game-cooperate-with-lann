#pragma once
#include "WindowApplicationBase.h"
#include "Timer.h"
#include "DirectUtility.h"

//使用Direct进行硬件加速渲染的窗体程序基类
//应继承此类并重写纯虚函数后使用
class DirectApplicationBase :
	public WindowApplicationBase
{
public:
	DirectApplicationBase(HINSTANCE hInstance);
	virtual ~DirectApplicationBase();

	//初始化（窗体及Direct）
	virtual bool Initialize() override;

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

	//当窗体大小被更改时会调用此函数
	virtual void OnResize() override;

	//窗体活动暂停
	virtual void Pause() override;

	//窗体活动恢复
	virtual void Resume() override;

protected:
	//初始化Direct3D
	bool InitializeDirect();

	//初始化Direct2D
	bool InitializeDirect2D();

	//获取MSAA质量等级
	//只会获取一次
	//如果想重新获取，则将mMsaaQualityLevels改为-1
	void QueryMsaaQualityLevel();

	virtual void Windowize() override;
private:
	Timer										mTimer;							//计时器

	ID3D11Device*						mDevice;							//设备
	ID3D11DeviceContext*			mImmediateContext;		//设备环境

	IDXGISwapChain*					mSwapChain;					//交换链

	UINT										mMsaaQualityLevels;		//MSAA抗锯齿质量等级

	ID3D11RenderTargetView*		mRenderTargetView;		//渲染对象视图
	ID3D11DepthStencilView*		mDepthStencilView;		//深度模板视图
	ID3D11Texture2D*					mDepthStencilBuffer;		//深度模板缓冲区

	ID2D1Factory*							mD2DFactory;					//D2D工厂模式接口
	ID2D1RenderTarget*				mD2DBackBufferRenderTarget;				//	D2D缓冲区渲染目标

	IDWriteFactory*						mDWriteFactory;				//D2D书写 工厂模式接口
	IDWriteTextFormat*				mWriteTextFormat;			//D2D书写 写字格式
	ID2D1SolidColorBrush*			mSolidBrush;					//D2D书写 笔刷
};

