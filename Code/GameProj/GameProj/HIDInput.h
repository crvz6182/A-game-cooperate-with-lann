#pragma once
#include "DirectUtility.h"

typedef char KeyboardState[256];

//���幤��ѧ�豸������
class HIDInput
{
public:
	~HIDInput();

	//��ȡ����
	static HIDInput* GetHIDInput();
	//���ٵ���
	static void DestroyHIDInput();

	//ѯ�ʵ�ǰ��������
	bool QueryInputs();

	//��ȡ��ǰ���̰���״̬
	char GetKeyState(DWORD macroKeys_DIK_);

	//��ʼ��
	bool Initialize(HINSTANCE hInstance, HWND hWindow);
	
	//�ͷ�
	ULONG Release();
private:
	HIDInput();

	//��ȡָ���豸�����뵽ָ����С��ָ��������
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);
private:
	IDirectInput8*							mInput;							//D3D�����
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//��������
	LPDIRECTINPUTDEVICE8			mMouseInput;					//�������

	DIMOUSESTATE						mMouseState;					//���״̬
	KeyboardState							mKeyboardState;				//����״̬
};