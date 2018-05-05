#pragma once

#define INITGUID

#include <d3d11.h>
#include <dwrite.h>
#include <dinput.h>
#include <assert.h>
#include <d3dcompiler.h>
#include "Math.h"
#include "String.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dwrite.lib")

//以全零初始化
#define ZeroInitialize(x) {ZeroMemory(&x, sizeof(x));}

#define CONSTGLOBAL XMGLOBALCONST

//用于检测函数执行结果
#ifndef HR
#define HR(x)																		\
	{																						\
		HRESULT hr = (x);														\
		if(FAILED(hr))																\
		{																					\
			TraceError( __FILE__, (DWORD)__LINE__, hr, L#x);	\
		}																					\
	}
#endif

template<typename ID3D>
inline void ReleaseCOM(ID3D*& d3dInterface)
{
	if (d3dInterface) {
		d3dInterface->Release();
		d3dInterface = nullptr;
	}
}

template<typename T>
void SafeDelete(const T * & ptr)
{
	if (ptr != nullptr) {
		delete ptr;
	}
	ptr = nullptr;
}

template<typename T>
void SafeDelete(const T * const& ptr)
{
	if (ptr != nullptr) {
		delete ptr;
	}
}

void TraceError(const char* fileName, DWORD lineNumber, HRESULT hr, const wchar_t* functionName);

namespace D3DUtil
{
	extern ID3D11Device*						gD3dDevice;
	extern ID3D11DeviceContext*		gImmediateDeviceContext;
	extern ID3D11RenderTargetView*	gRenderTargetView;
	extern ID3D11DepthStencilView*	gDepthStencilView;
	extern IDXGISwapChain*					gSwapChain;
}

template<typename T>
class Singleton
{
private:
	Singleton();
	virtual ~Singleton() = 0;

public:
	static Singleton* GetInstance()
	{
		static T* gInstance = new T;
		return gInstance;
	}
};