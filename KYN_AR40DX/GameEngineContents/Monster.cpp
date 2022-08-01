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

	{
		GameEngineCollision* Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 64.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	}
}

void Monster::Update(float _DeltaTime)
{
	Gravity(_DeltaTime);
}
