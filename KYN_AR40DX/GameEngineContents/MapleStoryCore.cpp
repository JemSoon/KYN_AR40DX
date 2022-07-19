#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/Stage1Level.h"

#pragma comment(lib, "GameEngineBase.lib")

MapleStoryCore::MapleStoryCore()
	: GameEngineCore()
{
}

MapleStoryCore::~MapleStoryCore()
{
}

void MapleStoryCore::Start()
{
	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	//Dir.Move("BlackSet");
	//GameEngineFolderTexture::Load(Dir.GetFullPath());

	// �̰� ����� �մϴ�.
	GameEngineTexture::Cut("LogIn.png", 1, 1);
	GameEngineTexture::Cut("idle.png", 3, 1);
	GameEngineTexture::Cut("walk.png", 4, 1);
	GameEngineTexture::Cut("stand.png", 2, 1);
	GameEngineTexture::Cut("Stage1.png", 1, 1);
	GameEngineTexture::Cut("Stage1_Col.png", 1, 1);
	GameEngineTexture::Cut("Stage1_BG.png", 1, 1);
	GameEngineTexture::Cut("Portal.png", 4, 1);
	GameEngineTexture::Cut("sugar.png", 1, 1);

	// ���ҽ��� �ε��ϴµ�.

	// RTTI �� Ÿ�� Ÿ�� �������̼�
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