#include "PreCompile.h"
#include "Potion.h"

Potion::Potion()
	:Time(0.0f)
{

}

Potion::~Potion()
{

}

void Potion::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 27, 27, 1 });
	Renderer->SetTexture("WhitePotion.png");
	Renderer->SetPivot(PIVOTMODE::BOT);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	Collision->GetTransform().SetLocalScale({ 20.0f, 20.0f, 100.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
	//Collision->SetCollisionMode(CollisionMode::Ex);
	Collision->ChangeOrder(OBJECTORDER::Item);

	StateManager.CreateStateMember("POP"
		, std::bind(&Potion::POPUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Potion::POPStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("DoomChit"
		, std::bind(&Potion::DoomChitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Potion::DoomChitStart, this, std::placeholders::_1));

	StateManager.ChangeState("POP");
}

void Potion::POPStart(const StateInfo& _Info)
{
	MovePower += float4::UP * 500.0f;
}

void Potion::POPUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//¶¥¿¡ ¶³¾îÁú¶§±îÁö ºù±Ûºù±Û
	Renderer->GetTransform().SetAddWorldRotation({ 0,0,GameEngineTime::GetDeltaTime() * 2000.0f,0 });

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)&&
		MovePower.y <= 0.0f)
	{
		StateManager.ChangeState("DoomChit");
	}
}

void Potion::DoomChitStart(const StateInfo& _Info)
{
	Renderer->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Renderer->GetTransform().SetWorldPosition({ 0,0,0,0 });
	Renderer->GetTransform().SetWorldRotation(float4::ZERO);
}

void Potion::DoomChitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Time += _DeltaTime * 5.0f;

	if ((int)Time % 2 == 0)
	{
		Renderer->GetTransform().SetLocalPosition({ 0.0f, 1.0f, 0.0f });
	}
	else if ((int)Time % 2 == 1)
	{
		Renderer->GetTransform().SetLocalPosition({ 0.0f, -1.0f, 0.0f });
	}
}

void Potion::Update(float _DeltaTime)
{
	ColorCheckUpdate();

	StateManager.Update(_DeltaTime);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	Gravity(_DeltaTime);
	

	NoGravity();
}
