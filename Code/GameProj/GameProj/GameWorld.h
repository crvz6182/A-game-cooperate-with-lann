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
	//PerformSystem							mPerformSystem;				//��������
	ID2D1RenderTarget*					mRenderTarget;					//��ȾĿ��
	Array<Actor*>								mActors;								//����
	HIDInput*									mInput;								//����
};

