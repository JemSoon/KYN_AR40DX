#include "PreCompile.h"
#include "Sugar.h"

Sugar::Sugar()
{

}

Sugar::~Sugar()
{

}

void Sugar::Start()
{
	//상속에 써둠
	//GetTransform().SetLocalScale({ 1, 1, 1 });
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 48, 75, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("sugar.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 40.0f,64.0f,100.0f });
		Collision->ChangeOrder(OBJECTORDER::NPC);
		Collision->GetTransform().SetWorldPosition({0,35.0f});
	}
}

void Sugar::Update(float _DeltaTime)
{
	ColorCheckUpdate();

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	{	
		//조건문 안해주면 계속 중력받아서 오차땜에 부들부들 떰
		Gravity(_DeltaTime);
	}

	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	NoGravity();
}

