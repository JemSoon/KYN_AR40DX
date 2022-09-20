#include "PreCompile.h"
#include "BossMano.h"
#include "Player.h"

#include "DamageNumber.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "BossHPUI.h"
BossMano::BossMano()
	:Damage(0)
	,PatternTime(0)
	,Random(0)
	,RandomDir(0)
	,BossUI(nullptr)
	,Num(nullptr)
{
	Speed = 25;

	MonsterAtt = 40;
	MonsterHPMax = 50;
	MonsterCurHP = MonsterHPMax;
}

BossMano::~BossMano()
{

}

void BossMano::Start()
{
	Monster::Start();

	BossUI = GetLevel()->CreateActor<BossHPUI>();
	BossUI->GetTransform().SetWorldPosition({ -329.0f,320.0f,-100.0f });
	BossUI->Off();

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
	Renderer->SetTexture("mano_idle.png");

	std::vector<unsigned int> Nine = { 0,1,2,3,4,5,6,7,8 };
	std::vector<unsigned int> Ten = { 0,1,2,3,4,5,6,7,8,9 };
	std::vector<unsigned int> Six = { 0,1,2,3,4,5 };
	std::vector<unsigned int> One = { 0};

	Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("mano_idle.png", Nine, 0.2f));
	Renderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("mano_move.png", Six, 0.2f));
	Renderer->CreateFrameAnimationCutTexture("Die", FrameAnimation_DESC("mano_die.png", Nine, 0.2f, false));
	Renderer->CreateFrameAnimationCutTexture("Buff", FrameAnimation_DESC("mano_skill1.png", Ten, 0.2f));
	Renderer->CreateFrameAnimationCutTexture("Hit", FrameAnimation_DESC("mano_hit.png", One, 0.2f, false));

	Renderer->ChangeFrameAnimation("Idle");
	Renderer->SetPivot(PIVOTMODE::BOT);

	{
		//애니메이션 엔드 관련
		Renderer->AnimationBindEnd("Die", std::bind(&BossMano::DieEnd, this));
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 90.0f, 80.0f, 100.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 35.0f, 0.0f });
		Collision->ChangeOrder(OBJECTORDER::Monster);
	}

	{
		SearchCollision = CreateComponent<GameEngineCollision>();
		SearchCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.1f });
		SearchCollision->GetTransform().SetLocalScale({ 300.0f, 80.0f, 100.0f });
		SearchCollision->GetTransform().SetLocalPosition({ 0.0f, 35.0f, 0.0f });
		SearchCollision->ChangeOrder(OBJECTORDER::MonsterSearch);
	}

	{
		StateManager.CreateStateMember("Idle"
			, std::bind(&BossMano::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&BossMano::IdleStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Move"
			, std::bind(&BossMano::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&BossMano::MoveStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Hit"
			, std::bind(&BossMano::HitUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&BossMano::HitStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Dead"
			, std::bind(&BossMano::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&BossMano::DeadStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Chase"
			, std::bind(&BossMano::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&BossMano::ChaseStart, this, std::placeholders::_1));

		StateManager.ChangeState("Idle");
	}
}


void BossMano::IdleStart(const StateInfo& _Info)
{
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	Renderer->ChangeFrameAnimation("Idle");
	MovePower = float4::ZERO;
}

void BossMano::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

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

	NoGravity();
	return;
}

void BossMano::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	RandomDir = Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
}

void BossMano::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	PatternTime += GameEngineTime::GetDeltaTime();

	if (RandomDir == 1)
	{
		//랜덤 방향1 == 왼쪽
		MovePower.x = -Speed;
		Renderer->GetTransform().PixLocalPositiveX();

		{
			//머리가 벽에 부딪히면 x움직임 0(MovePower.x로하면 부딪히면 떨어짐)
			if (false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::WHITE) &&
				false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::BLUE))
			{
				MovePower = 0.0f;
			}
		}
	}

	if (RandomDir == 2)
	{
		//랜덤 방향2 == 오른쪽
		MovePower.x = Speed;
		Renderer->GetTransform().PixLocalNegativeX();

		{
			//머리가 벽에 부딪히면 x움직임 0
			if (false == IsColor(COLORCHECKDIR::RIGHTTOP, CharacterObject::WHITE) &&
				false == IsColor(COLORCHECKDIR::RIGHTTOP, CharacterObject::BLUE))
			{
				MovePower = 0.0f;
			}
		}
	}

	if (Random == 1)
	{
		if (PatternTime >= 1.0f)
		{
			MovePower.x = 0.0f;
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	if (Random == 2)
	{
		if (PatternTime >= 2.0f)
		{
			MovePower.x = 0.0f;
			StateManager.ChangeState("Idle");
			PatternTime = 0;
		}
	}

	NoGravity();
	return;
}

void BossMano::HitStart(const StateInfo& _Info)
{
	BossUI->On();

	PatternTime = 0.0f;

	Renderer->ChangeFrameAnimation("Hit");

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

void BossMano::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	PatternTime += GameEngineTime::GetDeltaTime();
	MovePower.x = (PlayerInfo->GetDirX()) * 25.0f;

	if (PatternTime >= 0.5f)
	{
		StateManager.ChangeState("Chase");
	}

	NoGravity();
	return;
}

void BossMano::DeadStart(const StateInfo& _Info)
{
	PlayerInfo->CurEXP += 100;//달팽이는 5의 경험치를 준다
	MovePower = 0.0f;
	Renderer->ChangeFrameAnimation("Die");
	Collision->Off();
}

void BossMano::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void BossMano::ChaseStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Speed = 25.0f;
}

void BossMano::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	float4 Target = PlayerInfo->GetTransform().GetWorldPosition();
	float4 Me = this->GetTransform().GetWorldPosition();
	float Distance = (Target - Me).x;

	if (Distance < -10)
	{
		MovePower.x = -Speed;
		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (Distance > 10)
	{
		MovePower.x = Speed;
		Renderer->GetTransform().PixLocalNegativeX();
	}

	NoGravity();
	return;
}

//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//

void BossMano::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);

	BossUI->SetBoss(this);

	ColorCheckUpdate();
	StateManager.Update(_DeltaTime);

	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::PlayerAtt, CollisionType::CT_OBB2D,
			std::bind(&BossMano::BossManoHit, this, std::placeholders::_1, std::placeholders::_2));
	}
	{
		SearchCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Player, CollisionType::CT_OBB2D,
			std::bind(&BossMano::PlayerSearch, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool BossMano::PlayerSearch(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	StateManager.ChangeState("Chase");

	return true;
}

bool BossMano::BossManoHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//충돌한 몬스터만큼 ++
	PlayerInfo->MonsterCount += 1;

	Damage = PlayerInfo->GetPlayerAtt();

	if (PlayerInfo->MonsterHit(PlayerInfo->GetCollision(), this->GetCollision()) == true)
	{
		//플레이어 충돌 판정true시에만 피를 깐다
		HPRenderer->On();
		HPbarRenderer->On();
		MonsterCurHP = MonsterCurHP - Damage;
	}

	if (MonsterCurHP <= 0)
	{
		MonsterCurHP = 0;
		StateManager.ChangeState("Dead");
		//_This->GetActor()->Death();
	}

	else
	{
		//else 안걸어주면 몬스터가 안죽는다
		if (PlayerInfo->MonsterHit(PlayerInfo->GetCollision(), this->GetCollision()) == true)
		{
			//한마리 판정이 true면 Hit상태 당첨이고 충돌역시 true
			StateManager.ChangeState("Hit");
			return true;
		}

		else
		{
			//아니라면 아닌거
			return false;
		}
	}
}

void BossMano::DieEnd()
{
	Renderer->Off();
	HPbarRenderer->Off();
	HPRenderer->Off();
	Collision->Off();
	BossUI->Off();
	//Death();
}