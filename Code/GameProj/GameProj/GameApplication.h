#pragma once
#include "DirectApplicationBase.h"
#include "GameWorld.h"

class GameApplication : public DirectApplicationBase
{
public:
	GameApplication(HINSTANCE hInstance);
	virtual ~GameApplication() override;

	virtual bool Initialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw() override;

	virtual void OnResize() override;

private:

	//初始化Direct输入
	bool InitializeDirectInput();

	//初始化Direct2D
	bool InitializeDirect2D();
protected:

	ID2D1Factory*							mD2DFactory;					//D2D工厂模式接口
	ID2D1RenderTarget*				mD2DBackBufferRenderTarget;				//	D2D缓冲区渲染目标

	IDWriteFactory*						mDWriteFactory;				//D2D书写 工厂模式接口
	IDWriteTextFormat*				mWriteTextFormat;			//D2D书写 写字格式
	ID2D1SolidColorBrush*			mSolidBrush;					//D2D笔刷

	HIDInput*								mInput;							//输入


																			/********测试使用的成员变量********/
	GameWorld*							mWorld;							//世界
};

