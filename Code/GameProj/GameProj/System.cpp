#include "stdafx.h"
#include "System.h"

void MovementSystem::OperateEntities(EntityManager & entityManager, TimeSlotInSecond dt)
{
	for (Index i = 0; i < entityManager.entities.GetLength(); ++i) {
		if (!CanBeOperated(entityManager.entities[i])) {
			continue;
		}

		entityManager.mPositionComponents[i].position += (entityManager.mVelocityComponents[i].velocity * dt);
	}
}
