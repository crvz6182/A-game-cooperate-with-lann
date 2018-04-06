#pragma once
#include "Timer.h"
#include "HIDInput.h"
#include "PerformSystem.h"
#include "Actor.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	static GameWorld* GetWorld();
	static void DestroyWorld();

	bool Initialize(ID2D1RenderTarget* renderTarget);

	void SetRenderTarget(ID2D1RenderTarget* renderTarget);

	void RegisterActor(Actor* actor);

	void Update(TimeSlotInSecond deltaSecond);

	void Perform();

private:

private:
	//PerformSystem							mPerformSystem;				//表现世界
	ID2D1RenderTarget*					mRenderTarget;					//渲染目标
	Array<Actor*>								mActors;								//对象
	HIDInput*									mInput;								//输入
};

