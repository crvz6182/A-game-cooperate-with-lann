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

	//��ʼ��Direct����
	bool InitializeDirectInput();

	//��ʼ��Direct2D
	bool InitializeDirect2D();
protected:

	ID2D1Factory*							mD2DFactory;					//D2D����ģʽ�ӿ�
	ID2D1RenderTarget*				mD2DBackBufferRenderTarget;				//	D2D��������ȾĿ��

	IDWriteFactory*						mDWriteFactory;				//D2D��д ����ģʽ�ӿ�
	IDWriteTextFormat*				mWriteTextFormat;			//D2D��д д�ָ�ʽ
	ID2D1SolidColorBrush*			mSolidBrush;					//D2D��ˢ

	HIDInput*								mInput;							//����


																			/********����ʹ�õĳ�Ա����********/
	GameWorld*							mWorld;							//����
};

