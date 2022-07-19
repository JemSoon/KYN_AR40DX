#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

Monster::Monster()
	: Renderer(nullptr)
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 64, 64, 100 });
		Renderer->SetTexture("stand.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("stand.png", 0, 1, 0.3f));

		Renderer->ChangeFrameAnimation("Idle");
	}
}
