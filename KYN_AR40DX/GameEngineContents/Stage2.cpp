#include "Stage2.h"

Stage2::Stage2()
	: BG(nullptr)
	, Map(nullptr)
	, Portal(nullptr)
	, Map_Col(nullptr)
	, Speed(10.0f)
{

}

Stage2::~Stage2()
{

}

void Stage2::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("BGLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("BGLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("BGRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("BGUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("BGDown", VK_DOWN);
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{	//컬러충돌 맵
		Map_Col = CreateComponent<GameEngineTextureRenderer>();
		Map_Col->GetTransform().SetLocalScale({ 1420, 760, 100 });
		Map_Col->SetTexture("stage2_Col.png");

		//뒷배경	얘를 카메라이동 반응을 1초정도 느리게 쫓아오게 하고 싶다..
		BG = CreateComponent<GameEngineTextureRenderer>();
		BG->GetTransform().SetLocalScale({ 1420, 760, 100 });
		BG->SetTexture("stage2_BG.png");
	}

	{	//진짜 그림 맵
		Map = CreateComponent<GameEngineTextureRenderer>();
		Map->GetTransform().SetLocalScale({ 1420, 760, 100 });
		Map->SetTexture("stage2.png");
	}

	{	//포탈 렌더러
		Portal = CreateComponent<GameEngineTextureRenderer>();
		Portal->GetTransform().SetLocalScale({ 90, 201, 100 });
		Portal->SetTexture("Portal.png");

		Portal->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
		Portal->ChangeFrameAnimation("Portal");
	}
}

void Stage2::Update(float _DeltaTime)
{
	{	//BG랜더러 천천히 쫓아오게끔
		if (true == GameEngineInput::GetInst()->IsPress("BGLeft"))
		{
			BG->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * (Speed)*_DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("BGRight"))
		{
			BG->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * (-Speed) * _DeltaTime);
		}
	}
}

