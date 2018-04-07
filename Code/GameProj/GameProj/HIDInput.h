#pragma once
#include "DirectUtility.h"
#include "Actor.h"

typedef char KeyboardState[256];										//����״̬
using KeyToBehavior = Dictionary<DWORD, String>;		//����ӳ�䵽�ַ���
using InputInformations = Array<Pair<String, Percent>>;		//������Ϣ

//������Ϊ״̬
enum ActionState
{
	Pressed = 0,
	Released = 1
};

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

	InputInformations GetBehaviours();

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

	KeyToBehavior						mKeyMap;						//����ӳ�䵽�����ַ���
};