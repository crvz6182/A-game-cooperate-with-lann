#pragma once
#include "WindowApplicationBase.h"
#include "Timer.h"

//ʹ��Direct����Ӳ��������Ⱦ�Ĵ���������
//Ӧ�̳д��ಢ��д���麯����ʹ��
class DirectApplicationBase :
	public WindowApplicationBase
{
public:
	DirectApplicationBase(HINSTANCE hInstance);
	virtual ~DirectApplicationBase();

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

	//������ͣ
	virtual void Pause() override;

	//�����ָ�
	virtual void Resume() override;
private:
	Timer mTimer;				//��ʱ��
};

