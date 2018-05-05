#pragma once

#include "Component.h"
#include "DirectUtility.h"
#include "ThirdParty\DirectXTex\DDSTextureLoader.h"

struct Sprite
{
	ID3D11ShaderResourceView*		shaderResourceView;
	ID3D11Resource*						resource;
};

struct SpriteComponent :public IComponent<ComponentType::Component_Sprite>
{
	String											spriteID;
	Point2D										offset;

	SpriteComponent() :spriteID(""), offset() {}
	~SpriteComponent() {}
};

class SpriteFactory
{
public:
	using SpriteStore = Dictionary<String, Sprite>;

	static SpriteComponent CreateSprite(const String& spriteID);

	static SpriteStore		gSpriteStore;
};