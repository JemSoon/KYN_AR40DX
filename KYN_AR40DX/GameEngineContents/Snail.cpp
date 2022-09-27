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
	MonsterAtt = 150;
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
			//������ �����ڵ�
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
		//�ִϸ��̼� ���� ����
		Renderer->AnimationBindEnd("Die", std::bind(&Snail::DieEnd, this));
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 32.0f, 24.0f, 100.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 13.0f, 0.0f });
		Collision->SetCollisionMode(CollisionMode::Ex);
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
		//���� ����1 == ����
		MovePower.x = -Speed;
		Renderer->GetTransform().PixLocalPositiveX();
		
		{
			//�Ӹ��� ���� �ε����� x������ 0(MovePower.x���ϸ� �ε����� ������)
			if (false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::WHITE) &&
				false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::BLUE))
			{
				MovePower = 0.0f;
			}
		}
	}

	if (RandomDir == 2)
	{
		//���� ����2 == ������
		MovePower.x = Speed;
		Renderer->GetTransform().PixLocalNegativeX();

		{
			//�Ӹ��� ���� �ε����� x������ 0
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
			//�¾Ƽ� ���� ���� ����
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
	MovePower = 0.0f;
	Renderer->ChangeFrameAnimation("Die");
	Collision->Off();
	PlayerInfo->CurEXP += 1000;
}

void Snail::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
}

void Snail::ChaseStart(const StateInfo& _Info)
{
	Collision->ResetExData();
	MonsterHit = false;
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

		Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, 2, CollisionType::CT_OBB2D,
			std::bind(&Snail::SnailHit, this, std::placeholders::_1, std::placeholders::_2));
	}

	if (PlayerInfo->GetSlashBlastCollision()->IsUpdate() == false)
	{
		//MonsterHit = false;
		Collision->ResetExData();
	}

	MonsterRespawn();
}

bool Snail::SnailHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//�浹�� ���͸�ŭ ++
	//if (MonsterHit == false)
	{
		PlayerInfo->MonsterCount += 1;
		{
			//�ݸ��� �浹����(�����ݸ��� or ��ų �ݸ���)
			if ((PlayerInfo->MonsterHit(PlayerInfo->GetAttCollision(), this->GetCollision()) == true) &&
				/*(PlayerInfo->MonsterCount <= 1) &&*/
				true == PlayerInfo->GetAttCollision()->IsUpdate())
			{
				//PlayerInfo->MonsterCount += 1;
				//�÷��̾� ���� �ݸ����� ������ ��ü �ݸ����� �浹 && �浹������ �Ѹ������� && ���� �ݸ����� ��������
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
				//PlayerInfo->MonsterCount += 1;
				//�÷��̾� ��ų �ݸ����� ������ ��ü �ݸ����� �浹 && �浹������ �ټ��������� && ��ų �ݸ����� ��������

				SlashBlastHit->CurAnimationReset();
				SlashBlastHit->On();
				PlayerInfo->SetPlayerAttBuff(1.0f);//��ų�� ���ݷ��� 300%
				Damage = PlayerInfo->GetFinalAtt();
				HPRenderer->On();
				HPbarRenderer->On();
				MonsterCurHP = MonsterCurHP - Damage;

				DamageRender = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
				float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
				DamageRender->GetTransform().SetWorldPosition({ Pos.x,Pos.y + 32,-400 });
				DamageRender->NumberSetting(PlayerInfo->GetFinalAtt());
			}

			if ((PlayerInfo->MonsterUpperChargeHit(PlayerInfo->GetUpperChargeCollision(), this->GetCollision()) == true) &&
				true == PlayerInfo->GetUpperChargeCollision()->IsUpdate())
			{
				PlayerInfo->SetPlayerAttBuff(1.0f);//��ų�� ���ݷ��� 250%..�����ε� int�� ��������..?
				Damage = PlayerInfo->GetFinalAtt();
				HPRenderer->On();
				HPbarRenderer->On();
				MonsterCurHP = MonsterCurHP - Damage;

				DamageRender = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
				float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
				DamageRender->GetTransform().SetWorldPosition({ Pos.x,Pos.y + 32,-400 });
				DamageRender->NumberSetting(PlayerInfo->GetFinalAtt());
			}

			if ((PlayerInfo->MonsterLeafAttackHit(PlayerInfo->GetLeafAttackCollision(), this->GetCollision()) == true) &&
				true == PlayerInfo->GetLeafAttackCollision()->IsUpdate())
			{
				PlayerInfo->SetPlayerAttBuff(1.0f);//��ų�� ���ݷ��� 250%..�����ε� int�� ��������..?
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

		//MonsterHit = true;//�ѹ��� �浹�ϰԲ�
	}
	if (MonsterCurHP <= 0)
	{
		MonsterCurHP = 0;
		StateManager.ChangeState("Dead");
	}

	else
	{
		//else �Ȱɾ��ָ� ���Ͱ� ���״´�
		if ((PlayerInfo->MonsterHit(PlayerInfo->GetAttCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetAttCollision()->IsUpdate())
		{
			//�Ѹ��� ������ true�� Hit���� ��÷�̰� �浹���� true
			StateManager.ChangeState("Hit");
			return true;
		}

		else if ((PlayerInfo->MonsterSlashBlastHit(PlayerInfo->GetSlashBlastCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetSlashBlastCollision()->IsUpdate())
		{
			//�Ѹ��� ������ true�� Hit���� ��÷�̰� �浹���� true
			StateManager.ChangeState("Hit");
			return true;
		}

		else if ((PlayerInfo->MonsterUpperChargeHit(PlayerInfo->GetUpperChargeCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetUpperChargeCollision()->IsUpdate())
		{
			//�Ѹ��� ������ true�� Hit���� ��÷�̰� �浹���� true
			StateManager.ChangeState("Hit");
			return true;
		}

		else if ((PlayerInfo->MonsterLeafAttackHit(PlayerInfo->GetLeafAttackCollision(), this->GetCollision()) == true) &&
			true == PlayerInfo->GetLeafAttackCollision()->IsUpdate())
		{
			//�Ѹ��� ������ true�� Hit���� ��÷�̰� �浹���� true
			StateManager.ChangeState("Hit");
			return true;
		}

		else
		{
			//�ƴ϶�� �ƴѰ�
			return false;
		}
	}
}

void Snail::DieEnd()
{
	Collision->ResetExData();
	Renderer->Off();
	HPbarRenderer->Off();
	HPRenderer->Off();
	Collision->Off();
	PatternTime = 0.0f;
	Random = GameEngineRandom::MainRandom.RandomInt(1, 2);
	//MonsterHit = false;
	//Death();
	//�ش� ������ ������ ��ǥ�� ��� ����������?
}

void Snail::MonsterRespawn()
{
	if (Renderer->IsUpdate() == false)
	{
		PatternTime += GameEngineTime::GetDeltaTime();

		DeathCheck = true;

		if (Random == 1&& PatternTime>=10.0f)
		{
			StateManager.ChangeState("Idle");
			MonsterCurHP = MonsterHPMax;
			PatternTime = 0.0f;
			Renderer->GetPixelData().MulColor.a = 0.0f;
			Renderer->On();
		}

		if (Random == 2 && PatternTime >= 8.0f)
		{
			StateManager.ChangeState("Idle");
			MonsterCurHP = MonsterHPMax;
			PatternTime = 0.0f;
			Renderer->GetPixelData().MulColor.a = 0.0f;
			Renderer->On();
		}
	}

	if (Renderer->IsUpdate() == true && DeathCheck==true)
	{
		Renderer->GetPixelData().MulColor.a += GameEngineTime::GetDeltaTime();
		if (Renderer->GetPixelData().MulColor.a >= 1.0f)
		{
			Renderer->GetPixelData().MulColor.a = 1.0f;
			Collision->On();
			DeathCheck = false;//��� ������ ����ġ ��û ��ڴ�(�ݸ����� �״µ��� ��������� ���������� �浹ó���Ǿ� ����ġ ��ӵ���)
		}
	}
}