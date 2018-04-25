#pragma once
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager() {}

	const Index GetNextEmptyEntity();

	Index CreateNewEntity(ComponentMaskType mask);

	Array<Entity>			entities;
	Dictionary<Index, PositionComponent>		mPositionComponents;
	Dictionary<Index, VelocityComponent>		mVelocityComponents;
	Dictionary<Index, AppearanceComponent>	mAppearanceComponents;
};