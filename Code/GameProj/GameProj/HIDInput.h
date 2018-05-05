#pragma once
#include "DirectUtility.h"
#include <functional>

//#define BindAction(str, state, func) BindActionBehaviour(str, state, std::bind(func, this))

constexpr UINT KEYBOARD_SIZE = 256;

//动作行为状态
enum ActionState
{
	Idle = 0,				//00
	Press = 1,				//01
	Release = 2,			//10
	Hold = 3,				//11
	ACTION_SIZE
};

using KeyboardState = ArrayFixed<char, KEYBOARD_SIZE>;		//按键当前状态
using KeyboardAction = ArrayFixed<ActionState, KEYBOARD_SIZE>;		//按键当前行为

using KeyToString = ArrayFixed<String, KEYBOARD_SIZE>;		//按键映射到字符串

using ActionBehavior = void(*)();

using StringToAction = Dictionary<Pair<String, ActionState>, std::function<void()>>;

//人体工程学设备输入类
class HIDInput
{
public:
	~HIDInput();

	//获取单例
	static HIDInput* GetHIDInput();
	//销毁单例
	static void DestroyHIDInput();

	//询问当前所有输入，并进行回调
	bool QueryInputsThenCallBack();

	//初始化
	bool Initialize(HINSTANCE hInstance, HWND hWindow);

	//将方法绑定到Action字符串
	void BindActionBehaviour(const String & str, ActionState actionState, std::function<void()> func);

	//释放
	ULONG Release();
private:
	HIDInput();

	//获取指定设备的输入到指定大小的指定缓冲区
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);

	//获取当前键盘按键状态
	bool GetKeyState(DWORD macroKeys_DIK_);

	//将按键绑定到字符串
	void BindKey(DWORD macroKey_DIK_, const String& str);

	//键盘命令回调
	void KeyboardCallBack();
private:
	IDirectInput8*							mInput;							//D3D输入层
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//键盘输入
	LPDIRECTINPUTDEVICE8			mMouseInput;					//鼠标输入

	DIMOUSESTATE						mMouseState;					//鼠标状态
	KeyboardState							mKeyboardState;				//键盘本次状态
	KeyboardState							mKeyboardPreviousState;				//键盘上次状态
	KeyboardAction						mKeyboardAction;			//键盘行为

	KeyToString								mKeyMap;						//按键映射到动作字符串

	StringToAction						mActionMap;
};