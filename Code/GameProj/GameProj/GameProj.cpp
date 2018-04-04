//GameProj.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GameProj.h"
#include "GameApplication.h"
#include "GameWorld.h"
#include "TestSquare.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//允许在调试模式下进行运行时内存检查
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	GameApplication app(hInstance);

	TestSquare* ts = new TestSquare;
	GameWorld::GetWorld()->RegisterActor(ts);

	if (!app.Initialize()) {
		return 0;
	}

	return app.RunApplication();
}
