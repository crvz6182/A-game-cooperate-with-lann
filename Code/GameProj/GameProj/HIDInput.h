#pragma once
#include "DirectUtility.h"
#include "Actor.h"

constexpr UINT KEYBOARD_SIZE = 256;

//������Ϊ״̬
enum ActionState
{
	Idle = 0,				//00
	Press = 1,				//01
	Release = 2,			//10
	Hold = 3,				//11
	ACTION_SIZE
};

using KeyboardState = ArrayFixed<char, KEYBOARD_SIZE>;
using KeyboardAction = ArrayFixed<ActionState, KEYBOARD_SIZE>;

using KeyToBehavior = ArrayFixed<String, KEYBOARD_SIZE>;		//����ӳ�䵽�ַ���
using InputInformations = Array<Pair<String, Percent>>;		//������Ϣ


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
	bool GetKeyState(DWORD macroKeys_DIK_);

	//��ʼ��
	bool Initialize(HINSTANCE hInstance, HWND hWindow);

	//�ͷ�
	ULONG Release();
private:
	HIDInput();

	//��ȡָ���豸�����뵽ָ����С��ָ��������
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);

	void BindKey(DWORD macroKey_DIK_, const String& str);
private:
	IDirectInput8*							mInput;							//D3D�����
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//��������
	LPDIRECTINPUTDEVICE8			mMouseInput;					//�������

	DIMOUSESTATE						mMouseState;					//���״̬
	KeyboardState							mKeyboardState;				//���̱���״̬
	KeyboardState							mPreviousState;				//�����ϴ�״̬
	KeyboardAction						mKeyboardAction;			//������Ϊ

	KeyToBehavior						mKeyMap;						//����ӳ�䵽�����ַ���

	InputInformations					mInformations;				//�û�������Ϣ
};