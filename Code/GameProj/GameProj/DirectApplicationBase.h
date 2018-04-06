#pragma once
#include "WindowApplicationBase.h"
#include "Timer.h"
#include "DirectUtility.h"
#include "HIDInput.h"

//ʹ��Direct����Ӳ��������Ⱦ�Ĵ���������
//Ӧ�̳д��ಢ��д���麯����ʹ��
class DirectApplicationBase :
	public WindowApplicationBase
{
public:
	DirectApplicationBase(HINSTANCE hInstance);
	virtual ~DirectApplicationBase();

	//��ʼ�������弰Direct��
	virtual bool Initialize() override;

	//���г���
	//Direct���������Ҫά��һ����ѭ����������к���������ͬ
	virtual int RunApplication() override;

	//ÿ����Чѭ������ô˺���
	//������Ϸ����
	//timeElapsed: �����ϴε��ô˺�����ȥ�˵�ʱ�䣨�룩
	virtual void Update(TimeSlotInSecond deltaTime);

	//ÿ����Чѭ������ô˺���
	//����ͼ��
	virtual void Draw();

	//�������С������ʱ����ô˺���
	virtual void OnResize() override;

	//������ͣ
	virtual void Pause() override;

	//�����ָ�
	virtual void Resume() override;

protected:
	//��ʼ��Direct3D
	bool InitializeDirect();

	//��ʼ��Direct����
	bool InitializeDirectInput();

	//��ʼ��Direct2D
	bool InitializeDirect2D();

	//��ȡMSAA�����ȼ�
	//ֻ���ȡһ��
	//��������»�ȡ����mMsaaQualityLevels��Ϊ-1
	void QueryMsaaQualityLevel();

	virtual void Windowize() override;
private:
	Timer										mTimer;							//��ʱ��

	ID3D11Device*						mDevice;							//�豸
	ID3D11DeviceContext*			mImmediateContext;		//�豸����

	IDXGISwapChain*					mSwapChain;					//������

	UINT										mMsaaQualityLevels;		//MSAA����������ȼ�

	ID3D11RenderTargetView*		mRenderTargetView;		//��Ⱦ������ͼ
	ID3D11DepthStencilView*		mDepthStencilView;		//���ģ����ͼ
	ID3D11Texture2D*					mDepthStencilBuffer;		//���ģ�建����

	ID2D1Factory*							mD2DFactory;					//D2D����ģʽ�ӿ�
	ID2D1RenderTarget*				mD2DBackBufferRenderTarget;				//	D2D��������ȾĿ��

	IDWriteFactory*						mDWriteFactory;				//D2D��д ����ģʽ�ӿ�
	IDWriteTextFormat*				mWriteTextFormat;			//D2D��д д�ָ�ʽ
	ID2D1SolidColorBrush*			mSolidBrush;					//D2D��д ��ˢ

	HIDInput*								mInput;							//����


	/********����ʹ�õĳ�Ա����********/
	Point2D mActorLocation;
};

