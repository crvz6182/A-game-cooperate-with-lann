#include "stdafx.h"
#include "EffectBase.h"

EffectBase::EffectBase(const String & file)
{
	ID3DBlob* errorBlob = nullptr;
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined _DEBUG || defined DEBUG
	shaderFlags = D3DCOMPILE_DEBUG;
#endif
	HRESULT hr = 0;
	hr = D3DX11CompileEffectFromFile(file, nullptr, nullptr, shaderFlags, 0, D3DUtil::gD3dDevice, &mEffect, &errorBlob);
	if (FAILED(hr)) {
		MessageBoxA(nullptr, (LPCSTR)errorBlob->GetBufferPointer(), "ERROR!", MB_OK);
	}
	ReleaseCOM(errorBlob);
}

EffectBase::~EffectBase()
{
	ReleaseCOM(mEffect);
}

Count EffectBase::GetPassCount() const
{
	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);
	return techDesc.Passes;
}

D3DX11_PASS_DESC EffectBase::GetPassDescriptionByIndex(Index ind) const
{
	D3DX11_PASS_DESC tAns;
	mTech->GetPassByIndex(ind)->GetDesc(&tAns);
	return tAns;
}

void EffectBase::Apply(Index i)
{
	mTech->GetPassByIndex(i)->Apply(0, D3DUtil::gImmediateDeviceContext);
}

PlainEffect::PlainEffect() : 
	EffectBase("Resource\\Shader\\LookDown2DSprite.fx")
{
	mTech = mEffect->GetTechniqueByName("LookDown2DSprite");
	mLocal2World = mEffect->GetVariableByName("gLocal_World")->AsMatrix();
	mWorld2View = mEffect->GetVariableByName("gWorld_View")->AsMatrix();
	mView2Proj = mEffect->GetVariableByName("gView_Projection")->AsMatrix();

	mSprite = mEffect->GetVariableByName("gSpriteMap")->AsShaderResource();
}

void PlainEffect::UpdateSprite(ID3D11ShaderResourceView * shaderResourceView)
{
	HR(mSprite->SetResource(shaderResourceView));
}

void PlainEffect::UpdateMatrixToVariable(ID3DX11EffectMatrixVariable * matVariable, const Matrix4x4 & mat)
{
	HR(matVariable->SetMatrix(reinterpret_cast<const float*>(&mat)));
}
