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
	// ���ҽ��� �ε��ϴµ�.

	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");

	ChangeLevel("Title");

	// ���������� ����
	// �� ���ӿ��� Ÿ��Ʋȭ��
	//            ��������1
	//            ��������2
}

void MapleStoryCore::UserGameUpdate()
{
	// ������ ����Ǿ���.
	// ������ ��� �޼���â�� �������Ѵ�.
}

void MapleStoryCore::UserGameEnd()
{
	int a = 0;
}
