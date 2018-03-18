#pragma once
#include "Timer.h"

using Size1D = int;

struct Size2D
{
	Size1D Weight;
	Size1D Height;
};

//ʹ��Direct���м�����Ⱦ�Ĵ���������
//Ӧ�̳��Դ��ಢ��д�麯����ʹ��
class DirectApplicationBase
{
public:
	//ʹ��ʵ�����г�ʼ��
	DirectApplicationBase(HINSTANCE instance);
	//����
	~DirectApplicationBase();


public:
	//��ȡ����ʵ��
	HINSTANCE GetApplicationInstance() const;
	//��ȡ������
	HWND GetWindowHandler() const;

	//���г���
	int RunApplication();
	//�˳�����
	void Quit();

	/*******************
	����Ϊ�麯��
	���麯�����뱻��д
	 *******************/

	//��ʼ������
	virtual bool Initialization();

	//�������С������ʱ����ô˺���
	virtual void OnResize();
	//ÿ����Чѭ������ô˺���
	//������Ϸ����
	//timeElapsed: �����ϴε��ô˺�����ȥ�˵�ʱ�䣨�룩
	virtual void Update(TimePointInSecond timeElapsed);
	//ÿ����Чѭ������ô˺���
	//����ͼ��
	virtual void Draw();
	//�Զ�����Ϣ����ص�����
	virtual LRESULT MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	//��ʼ��������
	bool InitializeMainWindow();
	//������ͣ
	void Pause();
	//�����ָ�
	void Resume();
	//���ڻ�����
	void Windowize();
	//��С������
	void Minimize();
	//��󻯴���
	void Maximize();
protected:
	HINSTANCE mApplicationInstance;		//����ʵ��
	HWND			mMainWIndowHandler;		//������
	Timer			mTimer;								//��ʱ��
	Size2D			mWindowSize;						//����
};

