#include "Stage1.h"

Stage1::Stage1()
	: BG(nullptr)
	, Map(nullptr)
	, Portal(nullptr)
	, Map_Col(nullptr)
{

}

Stage1::~Stage1()
{

}

void Stage1::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{	//컬러충돌 맵
		Map_Col = CreateComponent<GameEngineTextureRenderer>();
		Map_Col->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map_Col->SetTexture("Stage1_Col.png");

		//뒷배경	얘를 카메라이동 반응을 1초정도 느리게 쫓아오게 하고 싶다..
		BG = CreateComponent<GameEngineTextureRenderer>();
		BG->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		BG->SetTexture("Stage1_BG.png");
	}

	{	//진짜 그림 맵
		Map = CreateComponent<GameEngineTextureRenderer>();
		Map->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map->SetTexture("Stage1.png");
	}

	{	//포탈 렌더러
		Portal = CreateComponent<GameEngineTextureRenderer>();
		Portal->GetTransform().SetLocalScale({ 90, 201, 100 });
		Portal->SetTexture("Portal.png");

		Portal->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
		Portal->ChangeFrameAnimation("Portal");
	}
}

