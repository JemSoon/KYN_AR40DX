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
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
		Renderer->SetTexture("LogIn.png", 0);
	}

}

void TitleLogo::Update(float _DeltaTime)
{

}

void TitleLogo::End()
{
	int a = 0;
}