#include "PreCompile.h"
#include "Snail.h"
#include "Player.h"

#include "DamageNumber.h"

#include <GameEngineBase/GameEngineRandom.h>

Snail::Snail()
	:Damage(0)
	,PatternTime(0)
	,Random(0)
	,RandomDir(0)
	
	
{
	MonsterAtt = 15;
	MonsterHPMax = 15;
	MonsterCurHP = MonsterHPMax;
	Speed = 50;
}

Snail::~Snail()
{
}

void Snail::Start()
{
	Monster::Start();
	{
		{
			//선생님 예제코드
			//{
			//	//GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
			//	//Renderer->SetFolderTextureToIndex("Test", 0);
			//	//Renderer->ScaleToTexture();

			//	for (size_t i = 0; i < 100; i++)
			//	{
			//		float X = GameEngineRandom::MainRandom.RandomFloat(-1280 / 2, 1280 / 2);
			//		float Y = GameEngineRandom::MainRandom.RandomFloat(-720 / 2, 720 / 2);
			//		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
			//		Renderer->GetTransform().SetLocalPosition({ X, Y, 0 });
			//		Renderer->SetFolderTextureToIndex("Test", 0);
			//		Renderer->ScaleToTexture();
			//	}
			//}
		}
		HPRenderer->Off();
		HPbarRenderer->Off();

		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 64, 64, 1 });
		Renderer->SetTexture("snail_stand.png");

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
		Renderer->AnimationBindEnd("Die", std::bind(&Snail::DieEnd, this));
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
			, std::bind(&Snail::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Snail::IdleStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Move"
			, std::bind(&Snail::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Snail::MoveStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Hit"
			, std::bind(&Snail::HitUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Snail::HitStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Dead"
			, std::bind(&Snail::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Snail::DeadStart, this, std::placeholders::_1));

		StateManager.CreateStateMember("Chase"
			, std::bind(&Snail::ChaseUpdate, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&Snail::ChaseStart, this, std::placeholders::_1));

		StateManager.ChangeState("Idle");
	}
}

void Snail::IdleStart(const StateInfo& _Info)
{
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	Renderer->ChangeFrameAnimation("Idle");
	MovePower = float4::ZERO;
}

void Snail::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Snail::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	RandomDir = Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
}

void Snail::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Snail::HitStart(const StateInfo& _Info)
{
	PatternTime = 0.0f;
	{
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
}

void Snail::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	PatternTime += GameEngineTime::GetDeltaTime();
	MovePower.x = (PlayerInfo->GetDirX()) *25.0f;
	
	if (PatternTime >= 0.5f)
	{
		StateManager.ChangeState("Chase");
	}

	NoGravity();
	return;
}

void Snail::DeadStart(const StateInfo& _Info)
{
	PlayerInfo->CurEXP += 5;//달팽이는 5의 경험치를 준다
	MovePower = 0.0f;
	Renderer->ChangeFrameAnimation("Die");
	Collision->Off();
}

void Snail::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Snail::ChaseStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
	Speed = 50.0f;
}

void Snail::ChaseUpdate(float _DeltaTime, const StateInfo& _Info)
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

void Snail::Update(float _DeltaTime)
{
	Monster::Update(_DeltaTime);

	ColorCheckUpdate();
	StateManager.Update(_DeltaTime);

	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::PlayerAtt, CollisionType::CT_OBB2D,
			std::bind(&Snail::SnailHit, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Snail::SnailHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//충돌한 몬스터만큼 ++
	PlayerInfo->MonsterCount += 1;
	
	//Damage = PlayerInfo->GetFinalAtt();이걸 여기다 선언하지말고 각 콜리전마다 해줘야함

	//if (PlayerInfo->MonsterHit(PlayerInfo->GetAttCollision(), this->GetCollision()) == true)
	//{
	//	//플레이어 충돌 판정true시에만 피를 깐다
	//	HPRenderer->On();
	//	HPbarRenderer->On();
	//	PlayerInfo->SetPlayerAttBuff(1.0f);
	//	MonsterCurHP = MonsterCurHP - Damage;
	//}

	//if (PlayerInfo->MonsterCount <= 1)
	//{	//이거 몬스터쪽으로 옮겨야할듯
	//	//몬스터를 한마리 쳤을때만 띄운다
	//	//플레이어의 공격력을 가져와 몬스터 액터에 그 숫자(데미지)를 머리위에 띄운다
	//	DamageRender = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
	//	float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
	//	DamageRender->GetTransform().SetWorldPosition({ Pos.x,Pos.y + 32,-400 });
	//	DamageRender->NumberSetting(PlayerInfo->GetFinalAtt());
	//}
	{
		//콜리전 충돌관련(공격콜리전 or 스킬 콜리전)
		if ((PlayerInfo->MonsterHit(PlayerInfo->GetAttCollision(), this->GetCollision()) == true) &&
			/*(PlayerInfo->MonsterCount <= 1) &&*/
			true == PlayerInfo->GetAttCollision()->IsUpdate())
		{
			//플레이어 공격 콜리전과 달팽이 본체 콜리전이 충돌 && 충돌마리수 한마리이하 && 공격 콜리전이 켜졌을때
			PlayerInfo->SetPlayerAttBuff(1.0f);
			Damage = PlayerInfo->GetFinalAtt();
			HPRenderer->On();
			HPbarRenderer->On();
			MonsterCurHP = MonsterCurHP - Damage;

			DamageRender = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
			float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
			DamageRender->GetTransform().SetWorldPosition({ Pos.x,Pos.y + 32,-400 });
			DamageRender->NumberSetting(PlayerInfo->GetFinalAtt());
		}

		if ((PlayerInfo->MonsterSlashBlastHit(PlayerInfo->GetSlashBlastCollision(), this->GetCollision()) == true) &&
			/*(PlayerInfo->MonsterCount <= 5) &&*/
			true == PlayerInfo->GetSlashBlastCollision()->IsUpdate())
		{
			//플레이어 스킬 콜리전과 달팽이 본체 콜리전이 충돌 && 충돌마리수 다섯마리이하 && 스킬 콜리전이 켜졌을때
			PlayerInfo->SetPlayerAttBuff(3.0f);//스킬은 공격력의 300%
			Damage = PlayerInfo->GetFinalAtt();
			HPRenderer->On();
			HPbarRenderer->On();
			MonsterCurHP = MonsterCurHP - Damage;

			DamageRender = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
			float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
			DamageRender->GetTransform().SetWorldPosition({ Pos.x,Pos.y + 32,-400 });
			DamageRender->NumberSetting(PlayerInfo->GetFinalAtt());
		}
	}

	if (MonsterCurHP <= 0)
	{
		MonsterCurHP = 0;
		StateManager.ChangeState("Dead");
	}

	else
	{
		//else 안걸어주면 몬스터가 안죽는다
		if ((PlayerInfo->MonsterHit(PlayerInfo->GetAttCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetAttCollision()->IsUpdate())
		{
			//한마리 판정이 true면 Hit상태 당첨이고 충돌역시 true
			StateManager.ChangeState("Hit");
			return true;
		}

		else if ((PlayerInfo->MonsterSlashBlastHit(PlayerInfo->GetSlashBlastCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetSlashBlastCollision()->IsUpdate())
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

void Snail::DieEnd()
{
	Renderer->Off();
	HPbarRenderer->Off();
	HPRenderer->Off();
	Collision->Off();
	//Death();
	//해당 레벨의 리스폰 좌표를 어떻게 가져오느냐?
}
