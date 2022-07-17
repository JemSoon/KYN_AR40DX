#include <Windows.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <GameEngineContents/MapleStoryCore.h>//내 게임은 메이플
#include <GameEngineBase/GameEngineMath.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		lpCmdLine,
	_In_ int		nCmdShow)
{
	new int();

	GameEngineCore::Start<MapleStoryCore>();
	return 0;
}