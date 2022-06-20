#include "MapleStoryCore.h"
#include "TitleLevel.h"
#include "Stage1Level.h"

#pragma comment(lib, "GameEngineBase.lib")


MapleStoryCore::MapleStoryCore() 
	:GameEngineCore()
{
}

MapleStoryCore::~MapleStoryCore() 
{
}

void MapleStoryCore::UserGameStart()
{
	// 리소스를 로드하는데.

	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");

	ChangeLevel("Title");

	// 게임컨텐츠 정의
	// 이 게임에는 타이틀화면
	//            스테이지1
	//            스테이지2
}

void MapleStoryCore::UserGameUpdate()
{
	// 서버가 종료되었어.
	// 무조건 경고 메세지창을 띄워줘야한다.
}

void MapleStoryCore::UserGameEnd()
{
	int a = 0;
}
