#include "stdafx.h"
#include "GameWorld.h"

namespace {
	GameWorld* gWorld = new GameWorld;
}

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
	for (auto & actor : mActors) {
		delete actor;
	}
}

GameWorld * GameWorld::GetWorld()
{
	return gWorld;
}

void GameWorld::DestroyWorld()
{
	delete gWorld;
}

bool GameWorld::Initialize(ID2D1RenderTarget* renderTarget)
{
	mInput = HIDInput::GetHIDInput();
	SetRenderTarget(renderTarget);

	for (auto& actor : mActors) {
		actor->OnInitialize();
	}

	return true;
}

void GameWorld::SetRenderTarget(ID2D1RenderTarget * renderTarget)
{
	mRenderTarget = renderTarget;
}

void GameWorld::RegisterActor(Actor * actor)
{
	mActors.Append(actor);
}

void GameWorld::Update(TimeSlotInSecond deltaSecond)
{
	for (auto& actor : mActors) {
		actor->Update(deltaSecond);
	}
}

void GameWorld::Perform()
{
	for (auto& actor: mActors) {
		actor->Draw(mRenderTarget);
	}
}
