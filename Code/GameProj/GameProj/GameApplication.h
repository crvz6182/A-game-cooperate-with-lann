#pragma once
#include "DirectApplicationBase.h"
#include "GameWorld.h"
#include "Log.h"

class GameApplication : public DirectApplicationBase
{
public:
	GameApplication(HINSTANCE hInstance);
	virtual ~GameApplication() override;

	virtual bool Initialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw() override;

	virtual void OnResize() override;

private:

	//初始化Direct输入
	bool InitializeDirectInput();

protected:
	HIDInput*								mInput;							//输入
	GameWorld*							mGameWorld;
};

