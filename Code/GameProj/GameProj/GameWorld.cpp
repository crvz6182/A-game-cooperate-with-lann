#include "stdafx.h"
#include "GameWorld.h"

GameWorld::GameWorld():mInput(nullptr)
{
}


GameWorld::~GameWorld()
{
}

bool GameWorld::Initialize()
{
	return true;
}

void GameWorld::Update(TimeSlotInSecond deltaSecond)
{
	mMovementSystem.OperateEntities(mEntityManager, deltaSecond);
}
