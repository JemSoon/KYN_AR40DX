#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

#include "DamageNumber.h"

#include <GameEngineBase/GameEngineRandom.h>

Monster::Monster()
	:Damage(15)
	,PatternTime(0)
	,Random(0)
	,RandomDir(0)
	,HP(15)
	,Hit(false)
	,nDamage(0)
	
{
	Speed = 50;
}

Monster::~Monster()
{
}

void Monster::Start()
{
	//상속에 써둠
	//GetTransform().SetLocalScale({ 1, 1, 1 });
	CharacterObject::Start();
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 64, 64, 1 });
		Renderer->SetTexture("snail_stand.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		std::vector<unsigned int> Nine = { 0,1,2,3,4,5,6,7,8 };
		std::vector<unsigned int> Five = { 0, 1, 2 ,3, 4, 3, 2, 1};
		std::vector<unsigned int> Three = { 0, 1, 2 };
		std::vector<unsigned int> Two = { 0, 1 };
		std::vector<unsigned int> One = { 0 };

		Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("snail_stand.png", One, 0.2f, false));
		Renderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("snail_move.png", Five, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Hit", FrameAnimation_DESC("snail_hit.png", One, 0.2f, false));
		Renderer->CreateFrameAnimationCutTexture("Die", FrameAnimation_DESC("snail_die.png", Nine, 0.1f, false));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	{
		//애니메이션 엔드 관련
		Renderer->AnimationBindEnd("Die", std::bind(&Monster::DieEnd, this));
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 32.0f, 24.0f, 100.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	}

	{
		StateManager.CreateStateMember("Idle"
			, std::bind(&Monster::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::IdleStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Move"
			, std::bind(&Monster::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::MoveStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Hit"
			, std::bind(&Monster::HitUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::HitStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Dead"
			, std::bind(&Monster::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::DeadStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Chase"
			, std::bind(&Monster::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Monster::ChaseStart, this, std::placeholders::_1));

		StateManager.ChangeState("Idle");
	}
}

void Monster::IdleStart(const StateInfo& _Info)
{
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	Renderer->ChangeFrameAnimation("Idle");
	Speed = 75.0f;
}

void Monster::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatternTime += GameEngineTime::GetDeltaTime();
	if (Random == 1)
	{
		if (PatternTime >= 1.0f)
		{
			StateManager.ChangeState("Move");
			PatternTime = 0;
		}
	}

	if (Random == 2)
	{
		if (PatternTime >= 2.0f)
		{
			StateManager.ChangeState("Move");
			PatternTime = 0;
		}
	}
}

void Monster::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	RandomDir = Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
}

void Monster::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatternTime += GameEngineTime::GetDeltaTime();
	//Random = GameEngineRandom::MainRandom.RandomInt(1, 4);
	if (Random == 1)
	{
		if (PatternTime >= 1.0f)
		{
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	if (Random == 2)
	{
		if (PatternTime >= 2.0f)
		{
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	if (RandomDir == 1)
	{
		//랜덤 방향1 == 왼쪽
		MovePower = GetTransform().GetLeftVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalPositiveX();

		if (true == IsNextColor(COLORCHECKDIR::DOWNL, float4::WHITE))
		{
			MovePower.x = 0.0f;
		}
	}

	if (RandomDir == 2)
	{
		//랜덤 방향2 == 오른쪽
		MovePower = GetTransform().GetRightVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalNegativeX();

		if (true == IsNextColor(COLORCHECKDIR::DOWNR, float4::WHITE))
		{
			MovePower.x = 0.0f;
		}
	}

	if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].b == 0) &&//다운이 그린
		iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].b == 0) &&//왼이 그린
		iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].g == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].r == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].b == 255)//왼탑이 화이트
	{	//언덕길은 위로 올리는힘이 추가
		MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
	}

	ColorCheckUpdateNext(MovePower);

	if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 255))) &&
		((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].r == 255))))
	{
		//양옆이 벽이 아니라면 움직인다
		GetTransform().SetWorldMove(MovePower);
	}
}

void Monster::HitStart(const StateInfo& _Info)
{
	PatternTime = 0.0f;
	if (PlayerInfo->OneAtt == true )
	{
		Renderer->ChangeFrameAnimation("Hit");

		//MovePower.x = (PlayerInfo->GetDirX()) * 0.5f;

		{
			//맞아서 보는 방향 설정
			if (PlayerInfo->GetDirX() > 0)
			{
				Renderer->GetTransform().PixLocalPositiveX();
			}

			if (PlayerInfo->GetDirX() < 0)
			{
				Renderer->GetTransform().PixLocalNegativeX();
			}
		}
	}

	Num->GetRenderer()->SetPivot(PIVOTMODE::TOP);
}

void Monster::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PatternTime += GameEngineTime::GetDeltaTime();
	MovePower.x = (PlayerInfo->GetDirX()) * 0.5f;
	GetTransform().SetWorldMove(MovePower);
	
	if (PatternTime >= 0.5f)
	{
		StateManager.ChangeState("Chase");
	}
}

void Monster::DeadStart(const StateInfo& _Info)
{
	PlayerInfo->CurEXP += 5;//달팽이는 5의 경험치를 준다
	MovePower = 0.0f;
	Renderer->ChangeFrameAnimation("Die");
	Collision->Off();
}

void Monster::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(MovePower);
}

void Monster::ChaseStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Speed = 50.0f;
}

void Monster::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Target = PlayerInfo->GetTransform().GetWorldPosition();
	float4 Me = this->GetTransform().GetWorldPosition();
	float Distance = (Target - Me).x;
	
	if (Distance < 0)
	{
		MovePower = GetTransform().GetLeftVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalPositiveX();
	}

	else if (Distance > 0)
	{
		MovePower = GetTransform().GetRightVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalNegativeX();
	}

	GetTransform().SetWorldMove(MovePower);
}

//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//

void Monster::Update(float _DeltaTime)
{
	if (PlayerInfo == nullptr)
	{
		PlayerInfo = Player::GetMainPlayer();
	}

	StateManager.Update(_DeltaTime);
	Gravity(_DeltaTime);

	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::PlayerAtt, CollisionType::CT_OBB2D,
			std::bind(&Monster::MonsterHit, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Monster::MonsterHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (PlayerInfo->OneAtt == false)
	{
		nDamage = PlayerInfo->GetPlayerAtt();
		HP = HP - (PlayerInfo->GetPlayerAtt());
		PlayerInfo->OneAtt = true;
	}

	//StateManager.ChangeState("Hit");
	
	if (HP <= 0)
	{
		HP = 0;
		StateManager.ChangeState("Dead");
		//_This->GetActor()->Death();
	}

	else
	{
		StateManager.ChangeState("Hit");
	}

	return true;
}

void Monster::DieEnd()
{
	Death();
}