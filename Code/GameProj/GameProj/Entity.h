#pragma once
#include "Component.h"
#include "SpriteComponent.h"

class Entity
{
public:
	Entity() : mComponentMask(0) {}
	~Entity() {}

	const bool ExistComponent(const ComponentMaskType& mask) const;

	const bool Valid() const;

	void AddComponents(ComponentMaskType mask);

	void RemoveComponents(ComponentMaskType mask);

private:
	ComponentMaskType mComponentMask;
};

