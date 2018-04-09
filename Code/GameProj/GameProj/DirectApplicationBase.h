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
	virtual void Update(TimeSlotInSecond deltaTime) = 0;

	//ÿ����Чѭ������ô˺���
	//����ͼ��
	virtual void Draw() = 0;

	//�������С������ʱ����ô˺���
	virtual void OnResize() override;

	//������ͣ
	virtual void Pause() override;

	//�����ָ�
	virtual void Resume() override;

	//��ǰ��Ϸ��ʱ��
	TimeSlotInSecond GetGameTime() const;

protected:
	//��ʼ��Direct3D
	bool InitializeDirect();


	//��ȡMSAA�����ȼ�
	//ֻ���ȡһ��
	//��������»�ȡ����mMsaaQualityLevels��Ϊ-1
	void QueryMsaaQualityLevel();

	virtual void Windowize() override;
protected:
	Timer										mTimer;							//��ʱ��

	ID3D11Device*						mDevice;							//�豸
	ID3D11DeviceContext*			mImmediateContext;		//�豸����

	IDXGISwapChain*					mSwapChain;					//������

	UINT										mMsaaQualityLevels;		//MSAA����������ȼ�

	ID3D11RenderTargetView*		mRenderTargetView;		//��Ⱦ������ͼ
	ID3D11DepthStencilView*		mDepthStencilView;		//���ģ����ͼ
	ID3D11Texture2D*					mDepthStencilBuffer;		//���ģ�建����

	VideoSettingConfig					mVideoSettingConfig;		//��Ƶ����
};

