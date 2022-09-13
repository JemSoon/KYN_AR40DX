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
	,Hit(false)
	
	
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
	//CharacterObject::Start();
	Monster::Start();
	{
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

	//if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].b == 0) &&//�ٿ��� �׸�
	//	iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g >= 200 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 0 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].b == 0) &&//���� �׸�
	//	iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].g == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].r == 255 && iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFTTOP)].b == 255)//��ž�� ȭ��Ʈ
	//{	//������� ���� �ø������� �߰�
	//	MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
	//}

	//if (((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::LEFT)].r == 255))) &&
	//	((iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g < 200) || (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].g == 255 && (iNextColorCheck[static_cast<unsigned int>(COLORCHECKDIR::RIGHT)].r == 255))))
	//{
	//	//�翷�� ���� �ƴ϶�� �����δ�
	//	GetTransform().SetWorldMove(MovePower);
	//}
}

void Snail::HitStart(const StateInfo& _Info)
{
	PatternTime = 0.0f;
	if (PlayerInfo->OneAtt == true )
	{
		Renderer->ChangeFrameAnimation("Hit");

		//MovePower.x = (PlayerInfo->GetDirX()) * 0.5f;

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
	PatternTime += GameEngineTime::GetDeltaTime();
	MovePower.x = (PlayerInfo->GetDirX()) * 0.5f;
	GetTransform().SetWorldMove(MovePower);
	
	if (PatternTime >= 0.5f)
	{
		StateManager.ChangeState("Chase");
	}
	
	NoGravity();
}

void Snail::DeadStart(const StateInfo& _Info)
{
	PlayerInfo->CurEXP += 5;//�����̴� 5�� ����ġ�� �ش�
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
	
	if (Distance < 0)
	{
		MovePower = GetTransform().GetLeftVector() * Speed;
		Renderer->GetTransform().PixLocalPositiveX();
	}

	else if (Distance > 0)
	{
		MovePower = GetTransform().GetRightVector() * Speed;
		Renderer->GetTransform().PixLocalNegativeX();
	}

	NoGravity();
}

//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//
//====================================================================================//

void Snail::Update(float _DeltaTime)
{
	//if (PlayerInfo == nullptr)
	//{
	//	PlayerInfo = Player::GetMainPlayer();
	//}

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
	Damage = PlayerInfo->GetPlayerAtt();

	if (PlayerInfo->OneAtt == false)
	{
		MonsterCurHP = MonsterCurHP - Damage;
		PlayerInfo->OneAtt = true;
	}

	//StateManager.ChangeState("Hit");
	
	if (MonsterCurHP <= 0)
	{
		MonsterCurHP = 0;
		StateManager.ChangeState("Dead");
		//_This->GetActor()->Death();
	}

	else
	{
		StateManager.ChangeState("Hit");
	}

	return true;
}

void Snail::DieEnd()
{
	Death();
}