#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/Stage1Level.h"
#include "GameEngineContents/Stage2Level.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/magic_enum.hpp>


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
	// string ����ȭ�� ���ѳ༮.
	std::string_view Value = magic_enum::enum_name(OBJECTORDER::Player);
	std::string Name = Value.data();
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Texture");
		Dir.Move("LevelUp");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Sound");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRessource(AllImageFileList[i].GetFullPath());
		}
	}

	// �̰� ����� �մϴ�.
	{	//�÷��̾� ��
		GameEngineTexture::Cut("idle.png", 3, 1);
		GameEngineTexture::Cut("jump.png", 1, 1);
		GameEngineTexture::Cut("prone.png", 1, 1);
		GameEngineTexture::Cut("walk.png", 4, 1);
		GameEngineTexture::Cut("sadari.png", 2, 1);
		GameEngineTexture::Cut("attack1.png", 3, 1);
		GameEngineTexture::Cut("attack2.png", 3, 1);
		GameEngineTexture::Cut("attack3.png", 3, 1);
		GameEngineTexture::Cut("attack4.png", 2, 1);
		GameEngineTexture::Cut("alert.png", 3, 1);
		GameEngineTexture::Cut("dead.png", 1, 1);
	}
	
	{	//����
		GameEngineTexture::Cut("stand.png", 2, 1); 
		GameEngineTexture::Cut("snail_stand.png", 1, 1);
		GameEngineTexture::Cut("snail_move.png", 5, 1);
		GameEngineTexture::Cut("snail_hit.png", 1, 1);
		GameEngineTexture::Cut("snail_die.png", 9, 1);
	}

	{	//�������� ��
		GameEngineTexture::Cut("LogIn.png", 1, 1);
		GameEngineTexture::Cut("Stage1.png", 1, 1);
		GameEngineTexture::Cut("Stage1_Col.png", 1, 1);
		GameEngineTexture::Cut("Stage1_BG.png", 1, 1);
		GameEngineTexture::Cut("Portal.png", 4, 1);
		GameEngineTexture::Cut("sugar.png", 1, 1);
		GameEngineTexture::Cut("stage2.png", 1, 1);
		GameEngineTexture::Cut("stage2_BG.png", 1, 1);
		GameEngineTexture::Cut("stage2_Col.png", 1, 1);
	}

	// ���ҽ��� �ε��ϴµ�.

	// RTTI �� Ÿ�� Ÿ�� �������̼�
	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");
	CreateLevel<Stage2Level>("Stage2");
	ChangeLevel("Stage2");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

	GameEngineFont::Load("�ü�");
}

void MapleStoryCore::Update(float _DeltaTime)
{
	// ������ ����Ǿ���.
	// ������ ��� �޼���â�� �������Ѵ�.
}

void MapleStoryCore::End()
{

}