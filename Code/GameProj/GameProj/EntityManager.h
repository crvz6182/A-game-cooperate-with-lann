#pragma once
#include "Entity.h"
#include "ComponentContainer.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager() {}

	const Index GetNextEmptyEntity();

	Index CreateNewEntity(ComponentMaskType mask);

	Array<Entity>			entities;
	ComponentContainer<PositionComponent>		mPositionComponents;
	ComponentContainer<VelocityComponent>		mVelocityComponents;
	ComponentContainer<AppearanceComponent>	mAppearanceComponents;
	ComponentContainer<SpriteComponent>			mSpriteComponents;
};