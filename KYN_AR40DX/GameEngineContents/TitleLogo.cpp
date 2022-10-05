#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

TitleLogo::TitleLogo()
	: TimeAngle(0.0f)
{
}

TitleLogo::~TitleLogo()
{
}

GameEngineRenderer* RendererTest = nullptr;

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
		std::vector<unsigned int> Idle = { 0, 1, 2, 1 };
		PlayerRenderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("idle.png", Idle, 0.3f));
		PlayerRenderer->ChangeFrameAnimation("Idle");
	}
}

void TitleLogo::Update(float _DeltaTime)
{

}

void TitleLogo::End()
{
	int a = 0;
}