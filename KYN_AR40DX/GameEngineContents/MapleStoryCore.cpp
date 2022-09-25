#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/Stage1Level.h"
#include "GameEngineContents/Stage2Level.h"
#include "GameEngineContents/Ship.h"
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
		Dir.Move("Texture");
		Dir.Move("Ship");

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
		GameEngineTexture::Cut("RIP.png", 7, 1);
		GameEngineTexture::Cut("SlashBlast1p.png", 1, 1);
		GameEngineTexture::Cut("SlashBlast2p.png", 2, 1);
		GameEngineTexture::Cut("UppperChargep.png", 1, 1);
		GameEngineTexture::Cut("LeafAttackp.png", 3, 1);
	}

	{
		//����Ʈ
		GameEngineTexture::Cut("SuperJump.png", 7, 1);
		GameEngineTexture::Cut("SlashBlast1.png", 5, 1);
		GameEngineTexture::Cut("SlashBlast2.png", 6, 1);
		GameEngineTexture::Cut("slashblasthit.png", 6, 1);
		GameEngineTexture::Cut("UppperCharge.png", 14, 1);
		GameEngineTexture::Cut("LeafAttack.png", 8, 1);
	}
	
	{	//����

		//��Ȳ����
		GameEngineTexture::Cut("stand.png", 2, 1);

		//������
		GameEngineTexture::Cut("snail_stand.png", 1, 1);
		GameEngineTexture::Cut("snail_move.png", 5, 1);
		GameEngineTexture::Cut("snail_hit.png", 1, 1);
		GameEngineTexture::Cut("snail_die.png", 9, 1);

		//����(����)
		GameEngineTexture::Cut("mano_idle.png", 9, 1);
		GameEngineTexture::Cut("mano_die.png", 9, 1);
		GameEngineTexture::Cut("mano_move.png", 6, 1);
		GameEngineTexture::Cut("mano_skill.png", 10, 1);
		GameEngineTexture::Cut("mano_hit.png", 1, 1);
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
	CreateLevel<Ship>("Ship");
	ChangeLevel("Stage1");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

	GameEngineFont::Load("�ü�");
	GameEngineFont::Load("�����ý��丮");
}

void MapleStoryCore::Update(float _DeltaTime)
{
	// ������ ����Ǿ���.
	// ������ ��� �޼���â�� �������Ѵ�.
}

void MapleStoryCore::End()
{

}