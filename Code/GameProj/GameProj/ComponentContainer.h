#pragma once
#include "Component.h"
#include "SpriteComponent.h"
#include "Math.h"

template<typename component>
class ComponentContainer
{
public:
	ComponentContainer() {}
	~ComponentContainer() {}

	auto& operator[](Index ind)
	{
		return mDictionary[ind];
	}
private:
	Dictionary<Index, component>		mDictionary;
};