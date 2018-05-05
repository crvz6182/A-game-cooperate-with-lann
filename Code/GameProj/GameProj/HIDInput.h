#pragma once
#include "DirectUtility.h"
#include <functional>

//#define BindAction(str, state, func) BindActionBehaviour(str, state, std::bind(func, this))

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

using KeyboardState = ArrayFixed<char, KEYBOARD_SIZE>;		//������ǰ״̬
using KeyboardAction = ArrayFixed<ActionState, KEYBOARD_SIZE>;		//������ǰ��Ϊ

using KeyToString = ArrayFixed<String, KEYBOARD_SIZE>;		//����ӳ�䵽�ַ���

using ActionBehavior = void(*)();

using StringToAction = Dictionary<Pair<String, ActionState>, std::function<void()>>;

//���幤��ѧ�豸������
class HIDInput
{
public:
	~HIDInput();

	//��ȡ����
	static HIDInput* GetHIDInput();
	//���ٵ���
	static void DestroyHIDInput();

	//ѯ�ʵ�ǰ�������룬�����лص�
	bool QueryInputsThenCallBack();

	//��ʼ��
	bool Initialize(HINSTANCE hInstance, HWND hWindow);

	//�������󶨵�Action�ַ���
	void BindActionBehaviour(const String & str, ActionState actionState, std::function<void()> func);

	//�ͷ�
	ULONG Release();
private:
	HIDInput();

	//��ȡָ���豸�����뵽ָ����С��ָ��������
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);

	//��ȡ��ǰ���̰���״̬
	bool GetKeyState(DWORD macroKeys_DIK_);

	//�������󶨵��ַ���
	void BindKey(DWORD macroKey_DIK_, const String& str);

	//��������ص�
	void KeyboardCallBack();
private:
	IDirectInput8*							mInput;							//D3D�����
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//��������
	LPDIRECTINPUTDEVICE8			mMouseInput;					//�������

	DIMOUSESTATE						mMouseState;					//���״̬
	KeyboardState							mKeyboardState;				//���̱���״̬
	KeyboardState							mKeyboardPreviousState;				//�����ϴ�״̬
	KeyboardAction						mKeyboardAction;			//������Ϊ

	KeyToString								mKeyMap;						//����ӳ�䵽�����ַ���

	StringToAction						mActionMap;
};