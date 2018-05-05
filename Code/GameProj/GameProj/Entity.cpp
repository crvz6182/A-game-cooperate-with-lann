#include "stdafx.h"
#include "Entity.h"

const bool Entity::ExistComponent(const ComponentMaskType & mask) const
{
	return ((mComponentMask & mask) == mask);
}

const bool Entity::Valid() const
{
	return (mComponentMask != ComponentType::Component_None);
}

void Entity::AddComponents(ComponentMaskType mask)
{
	mComponentMask |= mask;
}

void Entity::RemoveComponents(ComponentMaskType mask)
{
	mComponentMask &= (~mask);
}
