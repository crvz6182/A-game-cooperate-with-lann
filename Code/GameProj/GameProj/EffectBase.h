#pragma once
#include "String.h"
#include "DirectUtility.h"
#include "ThirdParty\\Effect11\\d3dx11effect.h"

class EffectBase
{
public:
	EffectBase(const String& file);
	virtual ~EffectBase();

	EffectBase(const EffectBase&) = delete;
	EffectBase& operator=(const EffectBase&) = delete;

	Count GetPassCount() const;

	D3DX11_PASS_DESC GetPassDescriptionByIndex(Index ind)const;

	void Apply(Index i);

protected:
	ID3DX11Effect * mEffect;

	ID3DX11EffectTechnique*				mTech;
};

namespace nsPlainEffect
{
	struct Vertex
	{
		DirectX::XMFLOAT2 localPosition;
		DirectX::XMFLOAT2 textureCoord;
	};
}

class PlainEffect : public EffectBase
{
public:
	PlainEffect();
	virtual ~PlainEffect() override {}

	void UpdateMatrixLocalToWorld(const Matrix4x4& mat) { UpdateMatrixToVariable(mLocal2World, mat); }
	void UpdateMatrixWorldToView(const Matrix4x4& mat) { UpdateMatrixToVariable(mWorld2View, mat); }
	void UpdateMatrixViewToProj(const Matrix4x4& mat) { UpdateMatrixToVariable(mView2Proj, mat); }

	void UpdateSprite(ID3D11ShaderResourceView* shaderResourceView);

private:
	void UpdateMatrixToVariable(ID3DX11EffectMatrixVariable* matVariable, const Matrix4x4& mat);
private:

	ID3DX11EffectMatrixVariable*		mLocal2World;
	ID3DX11EffectMatrixVariable*		mWorld2View;
	ID3DX11EffectMatrixVariable*		mView2Proj;

	ID3DX11EffectShaderResourceVariable*	mSprite;
};