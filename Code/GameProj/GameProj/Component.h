#pragma once
#include "Math.h"
#include "String.h"
#include "ECSUtil.h"

using namespace ECSUtil;

template<ComponentType componentType>
struct IComponent
{
	static inline ComponentType GetType() { return componentType; }
};

struct PositionComponent : public  IComponent<ComponentType::Component_Position>
{
public:
	Point2D position;

	PositionComponent(Unit _x = 0, Unit _y = 0) :position(_x, _y) {}
};

struct VelocityComponent : public IComponent<ComponentType::Component_Velocity>
{
public:
	Direction2D velocity;

	VelocityComponent(Unit _xDir = 0, Unit _yDir = 0) : velocity(_xDir, _yDir) {}
};

struct AppearanceComponent :public IComponent<ComponentType::Component_Appearance>
{
public:
	String name;

	AppearanceComponent(const String& str = "") :name(str) {}
};