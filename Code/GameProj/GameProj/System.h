#pragma once
#include "EntityManager.h"
#include "Timer.h"

template<typename FirstComponent, typename ... RestComponent>
class System
{
public:
	System() {};
	~System() {};

	const bool CanBeOperated(const Entity& entity) const
	{
		return entity.ExistComponent( GetMaskType<FirstComponent, RestComponent...>() );
	}

	virtual void OperateEntities(EntityManager& entities, TimeSlotInSecond dt) = 0;

private:
};


class MovementSystem :public System<PositionComponent, VelocityComponent>
{
public:
	MovementSystem() {}
	~MovementSystem() {};

	virtual void OperateEntities(EntityManager& entities, TimeSlotInSecond dt) override;

private:
};