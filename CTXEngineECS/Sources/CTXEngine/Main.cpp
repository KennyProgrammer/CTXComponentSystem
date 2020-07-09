#define _CRT_SECURE_NO_WARNINGS

#include "Windows.h"
#include "iostream"
#include "CTXEngineECS/ECSComponent.hpp"

using namespace CTXEngine::ECS;

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int mCmdShow)
{
#ifdef CTX_DEBUG
	AllocConsole();
	freopen("CONOUT$", "w+", stdout);
#endif

	while (true)
	{

	}

	return 0;
}