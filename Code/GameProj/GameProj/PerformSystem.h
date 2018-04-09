#pragma once
#include "Math.h"
#include "Texture.h"

class PerformSystem
{
public:
	PerformSystem();
	~PerformSystem();

	void Initialize(ID2D1RenderTarget* renderTarget);

private:
	Array<Array<Texture*>> mRenderSequence;
};

