#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{
	auto ind = CreateNewEntity(ComponentType::Component_Position | ComponentType::Component_Velocity | ComponentType::Component_Appearance | ComponentType::Component_Sprite);
	mSpriteComponents[ind] = SpriteFactory::CreateSprite("testman");

}

const Index EntityManager::GetNextEmptyEntity()
{
	for (Index i = 0; i < entities.GetLength(); ++i) {
		if (!entities[i].Valid()) {
			return i;
		}
	}
	entities.Append(Entity());
	return entities.GetLength() - 1;
}

Index EntityManager::CreateNewEntity(ComponentMaskType mask)
{
	Index ind = GetNextEmptyEntity();
	entities[ind].AddComponents(mask);
	return ind;
}
