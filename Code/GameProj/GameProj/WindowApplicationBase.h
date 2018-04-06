#pragma once
#include <windowsx.h>
#include "String.h"


//����������
//Ӧ�̳��Դ��ಢ��д�麯����ʹ��
class WindowApplicationBase
{
public:
	//ʹ��ʵ�����г�ʼ��
	WindowApplicationBase(HINSTANCE instance);
	//����
	virtual ~WindowApplicationBase();


public:
	//��ȡ����ʵ��
	HINSTANCE GetApplicationInstance() const;
	//��ȡ������
	HWND GetWindowHandler() const;

	//���г���
	virtual int RunApplication();
	//�˳�����
	void Quit();

	/*******************
	����Ϊ�麯��
	���麯�����뱻��д
	 *******************/

	//��ʼ������
	virtual bool Initialize();

	//�������С������ʱ����ô˺���
	virtual void OnResize();

	//�Զ�����Ϣ����ص�����
	virtual LRESULT MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//��ʼ��������
	bool InitializeMainWindow();

	//������ͣ
	virtual void Pause();
	//�����ָ�
	virtual void Resume();
	//���ڻ�����
	virtual void Windowize();
	//��С������
	virtual void Minimize();
	//��󻯴���
	virtual void Maximize();

protected:
	HINSTANCE mApplicationInstance;		//����ʵ��
	HWND			mMainWIndowHandler;		//������
	Size2D			mWindowSize;						//����
};

