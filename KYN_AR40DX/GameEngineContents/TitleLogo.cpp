#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

TitleLogo::TitleLogo()
	: TimeAngle(0.0f)
	, IsLevelMove(false)
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	// 1280 720
	GetTransform().SetLocalPosition({ 0, 0, 0 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 1 });
		Renderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 800.0f });
		Renderer->SetTexture("LogIn.png");
	}

	{
		PlayerRenderer = CreateComponent<GameEngineTextureRenderer>();
		PlayerRenderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		PlayerRenderer->GetTransform().SetLocalPosition({ -50.0f, -185.0f, 700.0f });
		PlayerRenderer->SetTexture("idle.png");
	}

	{
		LogoRenderer = CreateComponent<GameEngineTextureRenderer>();
		LogoRenderer->GetTransform().SetLocalScale({ 1280, 720, 1 });
		LogoRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 600.0f });
		LogoRenderer->SetTexture("Opening.png");
	}

	{
		PlayerCollision = CreateComponent<GameEngineCollision>();
		PlayerCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		PlayerCollision->GetTransform().SetLocalScale({ 32.0f, 64.0f, 100.0f });
		PlayerCollision->ChangeOrder(OBJECTORDER::Player);
		PlayerCollision->GetTransform().SetLocalPosition({ -50.0f, -185.0f, 700.0f });
	}

	{
		std::vector<unsigned int> Idle = { 0, 1, 2, 1 };
		std::vector<unsigned int> Three = { 0, 1, 2 };
		PlayerRenderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("idle.png", Idle, 0.3f));
		PlayerRenderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("walk.png", Three, 0.1f));
		PlayerRenderer->ChangeFrameAnimation("Idle");
	}
}

void TitleLogo::Update(float _DeltaTime)
{
	{
		PlayerCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Mouse, CollisionType::CT_OBB2D,
			std::bind(&TitleLogo::MouseThouch, this, std::placeholders::_1, std::placeholders::_2));
	}

	if (PlayerCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Mouse, CollisionType::CT_OBB2D,
		std::bind(&TitleLogo::MouseThouch, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		PlayerRenderer->ChangeFrameAnimation("Move");

		if (true == GameEngineInput::GetInst()->IsDown("Click"))
		{
			IsLevelMove = true;
		}
	}
	else
	{
		PlayerRenderer->ChangeFrameAnimation("Idle");
	}
}


bool TitleLogo::MouseThouch(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	
	return true;
}


void TitleLogo::End()
{
	int a = 0;
}