#include "stdafx.h"
#include "Texture.h"

ShapeTexture * Texture::CreateShape(Shapes shape)
{
	switch (shape)
	{
	case Shapes::RectangleShape:
		return new RectangleTexture;
	default:
		break;
	}
	return nullptr;
}

RectangleTexture::RectangleTexture()
{
	mSize.Width = 1;
	mSize.Height = 1;
}

RectangleTexture::~RectangleTexture()
{
}

void RectangleTexture::SetRectangle(Unit width, Unit height)
{
	mSize.Width = width;
	mSize.Height = height;
}

void RectangleTexture::Perform(ID2D1RenderTarget * renderTarget, const Transform2D & transform)
{
	UpdateSolidBrush(renderTarget);
	Point2D tLocation = transform.GetTranslation();
	D2D1_RECT_F tRectangleRegion = D2D1::RectF(tLocation.x, tLocation.y, tLocation.x + mSize.Width, tLocation.y + mSize.Height);
	renderTarget->DrawRectangle(tRectangleRegion, mSolidBrush);
}

ShapeTexture::~ShapeTexture()
{
	ReleaseCOM(mSolidBrush);
}

void ShapeTexture::UpdateSolidBrush(ID2D1RenderTarget * renderTarget)
{
	static ID2D1RenderTarget* gRenderTarget = nullptr;
	if (gRenderTarget != renderTarget) {
		ReleaseCOM(mSolidBrush);
		HR(renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &mSolidBrush));
	}
}
