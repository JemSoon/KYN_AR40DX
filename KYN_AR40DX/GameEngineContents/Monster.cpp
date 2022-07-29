#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	//상속에 써둠
	//GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 64, 64, 1 });
		Renderer->SetTexture("stand.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("stand.png", 0, 1, 0.2f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::BOT);
	}
}

void Monster::Update(float _DeltaTime)
{
	// Gravity();
}
