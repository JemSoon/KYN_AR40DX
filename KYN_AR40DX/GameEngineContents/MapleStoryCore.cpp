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

	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}

	// 이걸 해줘야 합니다.
	GameEngineTexture::Cut("Boss_Left.bmp", 5, 7);


	// 리소스를 로드하는데.

	// RTTI 런 타임 타입 인포메이션
	CreateLevel<TitleLevel>("Title");
	CreateLevel<Stage1Level>("Stage1");
	ChangeLevel("Stage1");

	// 게임컨텐츠 정의
	// 이 게임에는 타이틀화면
	//            스테이지1
	//            스테이지2
}

void MapleStoryCore::Update(float _DeltaTime)
{
	// 서버가 종료되었어.
	// 무조건 경고 메세지창을 띄워줘야한다.


}

void MapleStoryCore::End()
{
	int a = 0;
}