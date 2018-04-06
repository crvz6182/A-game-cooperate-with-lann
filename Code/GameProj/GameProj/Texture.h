#pragma once
#include "DirectUtility.h"
//#include "ThirdParty\DDSLoader\DDSTextureLoader.h"
#include "String.h"
#include "Transform.h"

/*
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment(lib, "ThirdParty\\DDSLoader\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "ThirdParty\\DDSLoader\\Release\\DirectXTex.lib")
#endif
*/

enum Shapes
{
	RectangleShape = 0
};

class ShapeTexture;

class Texture
{
public:
	//������״
	static ShapeTexture* CreateShape(Shapes shape);

	//������״
	virtual void Perform(ID2D1RenderTarget* renderTarget, const Transform2D& transform) = 0;
	/*
	Texture(ID3D11Device* device, const String& path);
	~Texture();

private:
	void LoadFromFile(const String& path);
private:
	ID3D11Device*								mDevice;								//D3D�豸
	ID3D11Resource*							mTexture2D;						//����ӿ�
	ID3D11ShaderResourceView*			mShaderResourceView;		//��Դ��ͼ*/
};

class ShapeTexture : public Texture
{
public:
	~ShapeTexture();
protected:
	virtual void UpdateSolidBrush(ID2D1RenderTarget * renderTarget);
protected:
	ID2D1SolidColorBrush * mSolidBrush;						//D2D��д ��ˢ
};

class RectangleTexture : public ShapeTexture
{
public:
	RectangleTexture();
	~RectangleTexture();

	void SetRectangle(Unit width, Unit height);

	virtual void Perform(ID2D1RenderTarget* renderTarget, const Transform2D& transform = Transform2D()) override;

private:

private:
	Size2D		mSize;
};
