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

void MapleStoryCore::UserStart()
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

void MapleStoryCore::UserUpdate(float _DeltaTime)
{
	// ������ ����Ǿ���.
	// ������ ��� �޼���â�� �������Ѵ�.
}

void MapleStoryCore::UserEnd()
{
	int a = 0;
}
