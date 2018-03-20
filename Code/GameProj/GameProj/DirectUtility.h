#pragma once

#include <d3d11.h>
#include <assert.h>

#pragma comment(lib, "d3d11.lib")

//�ͷ�Direct���
#define ReleaseCOM(x) {if(x){x->Release();}x=nullptr;}

//���ڼ�⺯��ִ�н��
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

void TraceError(const char* fileName, DWORD lineNumber, HRESULT hr, const wchar_t* functionName);