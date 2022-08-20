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
		Renderer->GetTransform().SetLocalScale({ 37, 26, 1 });
		Renderer->SetTexture("snail_stand.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		std::vector<unsigned int> Three = { 0, 1, 2 };
		std::vector<unsigned int> Two = { 0, 1 };
		std::vector<unsigned int> One = { 0 };

		Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("snail_stand.png", One, 0.2f, false));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 32.0f, 24.0f, 100.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	}
}

void Monster::Update(float _DeltaTime)
{
	Gravity(_DeltaTime);
}
