#pragma once
#include "Timer.h"
#include "HIDInput.h"
#include "Entity.h"
#include "System.h"
#include "SpriteSystem.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	bool Initialize();

	void Update(TimeSlotInSecond deltaSecond);

private:

private:
	HIDInput*									mInput;								// ‰»Î

	EntityManager								mEntityManager;

	MovementSystem						mMovementSystem;
	SpriteSystem								mSpriteSystem;
};

