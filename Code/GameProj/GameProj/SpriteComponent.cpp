#include "stdafx.h"
#include "SpriteComponent.h"

SpriteComponent SpriteFactory::CreateSprite(const String & spriteID)
{

	SpriteComponent tComponent = SpriteComponent();
	//hard code for temp
	if (spriteID == "testman") {
		Sprite tSprite;
		DirectX::CreateDDSTextureFromFile(
			D3DUtil::gD3dDevice,
			String("Resource\\testman.dds"),
			&tSprite.resource,
			&tSprite.shaderResourceView
		);
		SpriteFactory::gSpriteStore[spriteID] = tSprite;
		tComponent.spriteID = spriteID;
		tComponent.offset = Point2D(0.5, 0.5);
	}
	return tComponent;
}

SpriteFactory::SpriteStore	SpriteFactory::gSpriteStore;