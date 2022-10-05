#include "PreCompile.h"
#include "Item.h"

Item::Item()
	:Time(0.0f)
{

}

Item::~Item()
{

}

void Item::Start()
{
	Type = ItemType::Item;

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 27, 27, 1 });
	//Renderer->ScaleToTexture();
	Renderer->SetTexture("WhitePotion.png");
	Renderer->SetPivot(PIVOTMODE::BOT);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	Collision->GetTransform().SetLocalScale({ 20.0f, 20.0f, 100.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
	Collision->SetCollisionMode(CollisionMode::Ex);
	Collision->ChangeOrder(OBJECTORDER::Item);

	StateManager.CreateStateMember("POP"
		, std::bind(&Item::POPUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Item::POPStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("DoomChit"
		, std::bind(&Item::DoomChitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Item::DoomChitStart, this, std::placeholders::_1));

	StateManager.ChangeState("POP");
}

void Item::POPStart(const StateInfo& _Info)
{
	MovePower += float4::UP * 500.0f;
}

void Item::POPUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Item::DoomChitStart(const StateInfo& _Info)
{
	Renderer->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Renderer->GetTransform().SetWorldPosition({ 0,0,0,0 });
	Renderer->GetTransform().SetWorldRotation(float4::ZERO);
}

void Item::DoomChitUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Item::Update(float _DeltaTime)
{
	PlayerInfo = Player::GetMainPlayer();

	ColorCheckUpdate();

	StateManager.Update(_DeltaTime);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	Gravity(_DeltaTime);
	
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Item, CollisionType::CT_OBB2D,
			std::bind(&Item::PlayerEatCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	if (PlayerEatCheck(this->GetCollision(), PlayerInfo->GetCollision()) == true)
	{
		//PlayerInfo->ItemCount += 1;
	}

	NoGravity();
}

bool Item::PlayerEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{


	return true;
}