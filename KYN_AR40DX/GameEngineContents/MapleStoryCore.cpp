#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/Stage1Level.h"
#include "GameEngineContents/Stage2Level.h"
#include <GameEngineBase/GameEngineSound.h>

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

	// 이걸 해줘야 합니다.
	GameEngineTexture::Cut("LogIn.png", 1, 1);
	GameEngineTexture::Cut("idle.png", 3, 1);
	GameEngineTexture::Cut("walk.png", 4, 1);
	GameEngineTexture::Cut("stand.png", 2, 1);
	GameEngineTexture::Cut("Stage1.png", 1, 1);
	GameEngineTexture::Cut("Stage1_Col.png", 1, 1);
	GameEngineTexture::Cut("Stage1_BG.png", 1, 1);
	GameEngineTexture::Cut("Portal.png", 4, 1);
	GameEngineTexture::Cut("sugar.png", 1, 1);
	GameEngineTexture::Cut("stage2.png", 1, 1);
	GameEngineTexture::Cut("stage2_BG.png", 1, 1);
	GameEngineTexture::Cut("stage2_Col.png", 1, 1);

	// 리소스를 로드하는데.

	// RTTI 런 타임 타입 인포메이션
	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");
	CreateLevel<Stage2Level>("Stage2");
	ChangeLevel("Stage1");

}

void MapleStoryCore::Update(float _DeltaTime)
{
	// 서버가 종료되었어.
	// 무조건 경고 메세지창을 띄워줘야한다.
}

void MapleStoryCore::End()
{

}