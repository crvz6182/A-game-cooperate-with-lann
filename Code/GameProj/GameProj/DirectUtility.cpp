#include "stdafx.h"
#include "DirectUtility.h"

void TraceError(const char * fileName, DWORD lineNumber, HRESULT hr, const wchar_t * functionName)
{
	MessageBox(0, String(L"�ļ�����") + String(fileName) + String(L"\n�кţ�") + String((int)lineNumber) + String(L"\n�����룺") + String(hr) + String(L"\n������") + String(functionName), String(L"����"), 0);
}

namespace D3DUtil
{
	ID3D11Device*					gD3dDevice								= nullptr;
	ID3D11DeviceContext*		gImmediateDeviceContext		= nullptr;
	ID3D11RenderTargetView*	gRenderTargetView					= nullptr;
	ID3D11DepthStencilView*	gDepthStencilView					= nullptr;
	IDXGISwapChain*				gSwapChain								= nullptr;
}