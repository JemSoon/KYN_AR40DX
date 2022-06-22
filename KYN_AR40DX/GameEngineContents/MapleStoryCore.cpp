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

void MapleStoryCore::Start()
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

void MapleStoryCore::Update(float _DeltaTime)
{
	// ������ ����Ǿ���.
	// ������ ��� �޼���â�� �������Ѵ�.
}

void MapleStoryCore::End()
{
	int a = 0;
}
