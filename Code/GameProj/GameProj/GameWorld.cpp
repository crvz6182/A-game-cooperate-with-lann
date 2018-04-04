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

	for (Index i = 0; i < mActors.GetLength(); ++i) {
		mActors[i]->OnInitialize();
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
	for (Index i = 0; i < mActors.GetLength(); ++i) {
		mActors[i]->Update(deltaSecond);
	}
}

void GameWorld::Perform()
{
	for (Index i = 0; i < mActors.GetLength(); ++i) {
		mActors[i]->Draw(mRenderTarget);
	}
}
