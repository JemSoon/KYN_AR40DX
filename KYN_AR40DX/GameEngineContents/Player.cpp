#include "PreCompile.h"
#include "Player.h"
#include "Monster.h"

#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include "LevelParent.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "DamageNumber.h"

Player* Player::MainPlayer = nullptr;
Player* Player::BeforePlayer = nullptr;

Player::Player()
	:stop(false)
	, PortalOn(false)
	, PrevState("Idle")
	, Hit(false)
	, HitTime(0.0f)
	, HPMax(100)
	, CurHP(100)
	, MPMax(100)
	, CurMP(100)
	, HitDamage(0)
	, HitCheck(false)
	, EXPMax(10)
	, CurEXP(0)
	, PlayerLevel(1)
	, PlayerLevelUp(nullptr)
	, PlayerAtt(10)
	, JumpPower(500.0f)
	, Dir(float4::LEFT)
	, RIP(nullptr)
	, MonsterCount(0)
	, Effect(nullptr)
	, IsSkill(false)
	, UseSuperJump(5)
	, UseSlashBlast(10)
	, MyJob(JOB::NONE)
	, ManaDamage(0)
	, FinalAtt(PlayerAtt)
	, AttackCollision(nullptr)
	, SlashBlastCollision(nullptr)
	, GhostActor(nullptr)
	, IsLevelUp(false)
	, SlashBlast1(nullptr)
	, SlashBlast2(nullptr)
{
	MainPlayer = this;
	Speed = 150.0f;
	GroundMoveSpeed = 150.0f;
	JumpMoveSpeed = 100.0f;
	SuperJumpPower = 500.0f;
	PrevColor.g = 255;
}

Player::~Player()
{
}

void Player::Start()
{
	CharacterObject::Start();

	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PlayerJump", 'C');
		GameEngineInput::GetInst()->CreateKey("PlayerAttack", 'Z');
		GameEngineInput::GetInst()->CreateKey("SlashBlast", 'Q');
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		std::vector<unsigned int> Seven = { 0, 1, 2, 3, 4, 5, 6 };
		std::vector<unsigned int> Six = { 0, 1, 2, 3, 4, 5 };
		std::vector<unsigned int> Five = { 0, 1, 2, 3, 4 };

		RIP = CreateComponent<GameEngineTextureRenderer>();
		RIP->GetTransform().SetWorldScale({ 128,128,1 });
		RIP->CreateFrameAnimationCutTexture("RIP", FrameAnimation_DESC("RIP.png", Seven, 0.1f, false));
		RIP->ChangeFrameAnimation("RIP");
		RIP->SetPivot(PIVOTMODE::BOT);
		RIP->GetTransform().SetWorldPosition({ 0,-5 });
		RIP->Off();

		{
			//����Ʈ ��������
			Effect = CreateComponent<GameEngineTextureRenderer>();
			Effect->GetTransform().SetWorldScale({ 400,400,1 });
			Effect->GetTransform().SetWorldPosition({ 100,50,0 });
			Effect->CreateFrameAnimationCutTexture("SuperJump", FrameAnimation_DESC("SuperJump.png", Seven, 0.05f, false));
			Effect->ChangeFrameAnimation("SuperJump");
			Effect->Off();
			Effect->AnimationBindEnd("SuperJump", std::bind(&Player::SuperJumpEnd, this));
		}

		{
			//����Ʈ ������ ���Ʈ
			SlashBlast1 = CreateComponent<GameEngineTextureRenderer>();
			SlashBlast1->GetTransform().SetWorldScale({ 256,256,1 });
			SlashBlast1->GetTransform().SetWorldPosition({ 0,0,0 });
			SlashBlast1->SetPivot(PIVOTMODE::CENTER);
			SlashBlast1->CreateFrameAnimationCutTexture("SlashBlast1", FrameAnimation_DESC("SlashBlast1.png", Five, 0.05f, false));
			SlashBlast1->ChangeFrameAnimation("SlashBlast1");
			SlashBlast1->Off();
			SlashBlast1->AnimationBindEnd("SlashBlast1", std::bind(&Player::SlashBlast1End, this));

			SlashBlast2 = CreateComponent<GameEngineTextureRenderer>();
			SlashBlast2->GetTransform().SetWorldScale({ 512,512,1 });
			SlashBlast2->GetTransform().SetWorldPosition({ 0,0,0 });
			SlashBlast2->SetPivot(PIVOTMODE::CENTER);
			SlashBlast2->CreateFrameAnimationCutTexture("SlashBlast2", FrameAnimation_DESC("SlashBlast2.png", Six, 0.05f, false));
			SlashBlast2->ChangeFrameAnimation("SlashBlast2");
			SlashBlast2->Off();
			SlashBlast2->AnimationBindEnd("SlashBlast2", std::bind(&Player::SlashBlast2End, this));

			SlashBlast1->GetTransform().PixLocalPositiveX();
			SlashBlast2->GetTransform().PixLocalPositiveX();
			SlashBlast1->SetPivotToVector({ 40,60,-10 });
			SlashBlast2->SetPivotToVector({ -100, 60 ,-10 });
		}

		{
			GhostActor = GetLevel()->CreateActor<GameEngineActor>();

			GhostActor->SetParent(this);
		}

		Renderer = GhostActor->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->GetTransform().SetLocalPosition({ 100,0,0 });
		Renderer->SetTexture("idle.png");
		
		//Renderer->ScaleToTexture();//���� �������̶� �׷��� ���� ����

		std::vector<unsigned int> Idle = { 0, 1, 2, 1 };//������ ��� ���� �׽�Ʈ
		std::vector<unsigned int> Three = { 0, 1, 2};
		std::vector<unsigned int> Two = { 0, 1 };
		std::vector<unsigned int> One = { 0 };

		PlayerLevelUp = CreateComponent<GameEngineTextureRenderer>();
		PlayerLevelUp->CreateFrameAnimationFolder("LevelUp", FrameAnimation_DESC("LevelUp", 0.1f, false));
		PlayerLevelUp->SetScaleModeImage();
		PlayerLevelUp->ChangeFrameAnimation("LevelUp");
		PlayerLevelUp->SetPivotToVector({ 0.0f, 260.0f });
		PlayerLevelUp->Off();
		PlayerLevelUp->AnimationBindEnd("LevelUp", std::bind(&Player::LevelUpEnd, this));

		Renderer->CreateFrameAnimationCutTexture("Idle", FrameAnimation_DESC("idle.png", Idle, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("Move", FrameAnimation_DESC("walk.png", Three, 0.1f));
		Renderer->CreateFrameAnimationCutTexture("Sadari", FrameAnimation_DESC("sadari.png", Two, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("Jump", FrameAnimation_DESC("jump.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("Prone", FrameAnimation_DESC("prone.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("Attack1", FrameAnimation_DESC("attack1.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack2", FrameAnimation_DESC("attack2.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack3", FrameAnimation_DESC("attack3.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("Attack4", FrameAnimation_DESC("attack4.png", Two, 0.23f));
		Renderer->CreateFrameAnimationCutTexture("Alert", FrameAnimation_DESC("alert.png", Three, 0.23f));
		Renderer->CreateFrameAnimationCutTexture("Dead", FrameAnimation_DESC("dead.png", One, 0.23f, false));
		Renderer->CreateFrameAnimationCutTexture("SlashBlast1", FrameAnimation_DESC("SlashBlast1p.png", One, 0.01f, false));
		Renderer->CreateFrameAnimationCutTexture("SlashBlast2", FrameAnimation_DESC("SlashBlast2p.png", Two, 0.01f, false));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::CUSTOM);
	}
	
	{
		Renderer->AnimationBindEnd("Attack1", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack2", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack3", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack4", std::bind(&Player::AttackEnd, this));
	}

	{
		//��ü �ݸ���
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f,0.0f,0.0f,0.3f});
		Collision->GetTransform().SetLocalScale({ 32.0f, 64.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
		Collision->GetTransform().SetWorldPosition({ 0.0f,35.0f });
	}
	{
		//��Ÿ �ݸ���
		AttackCollision = CreateComponent<GameEngineCollision>();
		AttackCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		AttackCollision->GetTransform().SetLocalScale({ 84.0f, 64.0f, 100.0f });
		AttackCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		AttackCollision->GetTransform().SetWorldPosition({ -35.0f,35.0f });
		//AttackCollision->SetCollisionMode(CollisionMode::Ex);
		AttackCollision->Off();
	}
	{
		//������ ���Ʈ �ݸ���
		SlashBlastCollision = CreateComponent<GameEngineCollision>();
		SlashBlastCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,1.0f,0.0f,0.3f });
		SlashBlastCollision->GetTransform().SetLocalScale({ 250.0f, 150.0f, 100.0f });
		SlashBlastCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		SlashBlastCollision->GetTransform().SetWorldPosition({ -125.0f,75.0f });
		SlashBlastCollision->SetCollisionMode(CollisionMode::Ex);
		SlashBlastCollision->Off();
	}


	GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetText("12345", "�����ý��丮");
	Font->SetColor({ 1.0f, 0.0f, 0.0f });
	Font->SetScreenPostion({ 100.0f, 100.0f });

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1));

	int MyValue = 10;//�� �ۿ��ִ°�

	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::MoveStart, this, std::placeholders::_1));

	StateManager.CreateStateMember("Sadari"
		, std::bind(&Player::SadariUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SadariStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Jump"
		, std::bind(&Player::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::JumpStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("SuperJump"
		, std::bind(&Player::SuperJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SuperJumpStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Fall"
		, std::bind(&Player::FallUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FallStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Prone"
		, std::bind(&Player::ProneUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ProneStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Attack"
		, std::bind(&Player::AttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::AttackStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("DownJump"
		, std::bind(&Player::DownJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DownJumpStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Dead"
		, std::bind(&Player::DeadUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DeadStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("SlashBlast1"
		, std::bind(&Player::SlashBlast1Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlashBlast1Start, this, std::placeholders::_1));
	StateManager.CreateStateMember("SlashBlast2"
		, std::bind(&Player::SlashBlast2Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SlashBlast2Start, this, std::placeholders::_1));

	StateManager.ChangeState("Idle");

	JumpPower = 500.0f;
	GravitySpeed = 1500.0f;

	//���� �ɼǸ� �ٲٱ����� �ڵ�(�̿ϼ�)
	//Renderer->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
}

void Player::DeadStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Dead");
}

void Player::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	{	//����+����
		GhostActor->GetTransform().SetAddWorldRotation({ 0,0,_DeltaTime * 100.0f,0 });
		//ȸ�� ������ ����
		GhostActor->GetTransform().SetWorldPosition({ 0,10,0,0 });
		//������ ���� ����
		Renderer->GetTransform().SetWorldRotation(float4::ZERO);
		//Renderer->GetTransform().SetAddWorldRotation({ 0,0,_DeltaTime * GameEngineMath::RadianToDegree,0.0f });
	}
	return;
}

void Player::IdleStart(const StateInfo& _Info)
{
	AttackCollision->Off();
	PrevState = StateManager.GetCurStateStateName();
	Speed = GroundMoveSpeed;

	MovePower = float4::ZERO;

	if (Hit == false)
	{
		//��ҿ� idle�ִϸ��̼�
		Renderer->ChangeFrameAnimation("Idle");
	}
	else
	{
		//�¾����� Alert
		Renderer->ChangeFrameAnimation("Alert");
	}
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (HitTime >= 3.0f)
	{
		Renderer->ChangeFrameAnimation("Idle");
		Collision->On();
		Hit = false;
		HitTime = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		StateManager.ChangeState("Move");
		return;
	}

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	{
		StateManager.ChangeState("Fall");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		StateManager.ChangeState("Attack");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("SlashBlast"))
	{
		StateManager.ChangeState("SlashBlast1");
		return;
	}

	if ((true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::RED) ||
		true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)) &&
		true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Sadari");
		MovePower.y = 0.0f;
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Prone");
		return;
	}

	if (true == IsColor(COLORCHECKDIR::CENTER, CharacterObject::BLUE) &&
		true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		StateManager.ChangeState("Sadari");
		MovePower.y = 0.0f;
		return;
	}

	NoGravity();
	return;
}

void Player::AttackStart(const StateInfo& _Info)
{
	AttackCollision->On();

	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

	if (RandomNumber == 1)
	{
		Renderer->ChangeFrameAnimation("Attack1");
	}
	else if (RandomNumber == 2)
	{
		Renderer->ChangeFrameAnimation("Attack2");
	}
	else if (RandomNumber == 3)
	{
		Renderer->ChangeFrameAnimation("Attack3");
	}
	else
	{
		Renderer->ChangeFrameAnimation("Attack4");
	}


	Speed = GroundMoveSpeed;//�����Ҷ� �����𸣰� ���ǵ尡 -75�� �����;;
}

void Player::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{

	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);
	NoGravity();

	{
		//�����ϸ鼭 ����ġ�� �����Ҷ� ����Ű �����̸� ��� �����̸鼭 �����ؼ� �װ� ������
		if (MovePower.y == 0.0f)
		{
			MovePower.x = 0.0f;
		}
	}

	stop = true;
}

void Player::AttackEnd()
{
	MonsterCount = 0;

	if (true == GameEngineInput::GetInst()->IsFree("PlayerAttack"))
	{
		AttackCollision->Off();
		StateManager.ChangeState("Fall");
	}

	else if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		AttackCollision->On();
		int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

		if (RandomNumber == 1)
		{
			Renderer->ChangeFrameAnimation("Attack1");
		}
		else if (RandomNumber == 2)
		{
			Renderer->ChangeFrameAnimation("Attack2");
		}
		else if (RandomNumber == 3)
		{
			Renderer->ChangeFrameAnimation("Attack3");
		}
		else
		{
			Renderer->ChangeFrameAnimation("Attack4");
		}

		Speed = 150.0f;//�����Ҷ� �����𸣰� ���ǵ尡 -75�� �����;;
	}
}

void Player::ProneStart(const StateInfo& _Info)
{
	MovePower.y = 0.0f;//���� �� Ƣ������ �����
	Renderer->ChangeFrameAnimation("Prone");
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown")&&
		true == GameEngineInput::GetInst()->IsDown("PlayerJump")&&
		(ColorCheck[5].g>200 && ColorCheck[5].r <= 0 && ColorCheck[5].b <= 0))
	{
		//�׸�200 ���� �عٴ� 200�ٴ��� �� �������� ���Ѵ�
		StateManager.ChangeState("DownJump");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	Speed = GroundMoveSpeed;
	Renderer->ChangeFrameAnimation("Move");
	MovePower.y = 0.0f;
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//GameEngineDebug::DrawBox();

	// GameEngineDebug::DebugSphereRender();
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{	//�ƹ��͵� �ȴ����� �ְ� �ٴڿ������� Idle���·� ����
		StateManager.ChangeState("Idle");
		//MovePower = float4::ZERO;
		MovePower.x = 0.0f;
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Prone");
		MovePower.x = 0.0f;
		return;
	}

	{
		//�� �߳��� ȭ��Ʈ��� Fall����
		if (true == IsColor(COLORCHECKDIR::DOWNL, CharacterObject::WHITE)&&
			true == IsColor(COLORCHECKDIR::DOWNR, CharacterObject::WHITE))
		{
			StateManager.ChangeState("Fall");
			return;
		}
	}

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE))
	{
		MovePower.y = 0.0f;
		return;
	}

	{
		//�糡 �Ӹ��κ��� ���� �ε����� �����̴� ���� 0�̵ȴ�
		if (false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::WHITE) &&
			false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::BLUE) &&
			true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
		{
			MovePower = 0.0f;
			stop = true;
			return;
		}
		else if (false == IsColor(COLORCHECKDIR::RIGHTTOP, CharacterObject::WHITE) &&
			false == IsColor(COLORCHECKDIR::RIGHTTOP, CharacterObject::BLUE) &&
			true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
		{
			MovePower = 0.0f;
			stop = true;
			return;
		}
		else
		{
			//���� �ε����� �ƴ϶�� ��浵 ��������δ�
			stop = false;
		}
	}

	NoGravity();

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		MovePower.x = 0.0f;
		StateManager.ChangeState("Attack");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("SlashBlast")&&
		(CurMP >= ManaDamage))
	{
		MovePower.x = 0.0f;
		StateManager.ChangeState("SlashBlast1");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
		
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{	
		Dir = float4::RIGHT;
		{
			AttackCollision->GetTransform().SetLocalPosition({ 35.0f,35.0f }); 
			SlashBlastCollision->GetTransform().SetLocalPosition({ 125.0f,75.0f });
		}
		MovePower.x = Speed;
		Renderer->GetTransform().PixLocalNegativeX();
		{
			Effect->GetTransform().PixLocalNegativeX();
			Effect->SetPivotToVector({ -100,50,0 });
		}
		{
			SlashBlast1->GetTransform().PixLocalNegativeX();
			SlashBlast2->GetTransform().PixLocalNegativeX();
			SlashBlast1->SetPivotToVector({ -40,60 ,-10});
			SlashBlast2->SetPivotToVector({ 100, 60 ,-10 });
		}
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{	
		Dir = float4::LEFT;
		{
			AttackCollision->GetTransform().SetLocalPosition({ -35.0f,35.0f });
			SlashBlastCollision->GetTransform().SetLocalPosition({ -125.0f,75.0f });
		}
		MovePower.x = -Speed;
		Renderer->GetTransform().PixLocalPositiveX();
		{
			Effect->GetTransform().PixLocalPositiveX();
			Effect->SetPivotToVector({ 100,50,0 });
		}
		{
			SlashBlast1->GetTransform().PixLocalPositiveX();
			SlashBlast2->GetTransform().PixLocalPositiveX();
			SlashBlast1->SetPivotToVector({ 40,60,-10 });
			SlashBlast2->SetPivotToVector({ -100, 60 ,-10 });
		}
		return;
	}

}

void Player::SadariStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Sadari");
}

void Player::SadariUpdate(float _DeltaTime, const StateInfo& _Info)
{
	{
		//��ٸ��� ������ ���⼳����
		if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
		{
			Dir = float4::LEFT;
			Effect->GetTransform().PixLocalPositiveX();
			Effect->SetPivotToVector({ 100,50,0 });

		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
		{
			Dir = float4::RIGHT;
			Effect->GetTransform().PixLocalNegativeX();
			Effect->SetPivotToVector({ -100,50,0 });
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		Renderer->CurAnimationPauseOff();
		MovePower.y = Speed;
	}
	else if (false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		Renderer->CurAnimationPauseOn();
		MovePower.y = 0.0f;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		Renderer->CurAnimationPauseOff();
		MovePower.y = -Speed;
	}


	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::RED) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE) &&
		true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
		MovePower.y = 0.0f;
		return;
	}

	if (false == IsColor(COLORCHECKDIR::CENTER, CharacterObject::BLUE)&&
		false == IsColor(COLORCHECKDIR::CENTER, CharacterObject::RED)&&
		true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		StateManager.ChangeState("Idle");
		MovePower.y = 0.0f;
		return;
	}

	{
		//��ٸ��� ����Ű ������ ����
		if (true == GameEngineInput::GetInst()->IsPress("PlayerJump") &&
			(true == GameEngineInput::GetInst()->IsPress("PlayerLeft")))
		{
			MovePower.x = -Speed;
			Renderer->GetTransform().PixLocalPositiveX();
			StateManager.ChangeState("Jump");
		}
		else if (true == GameEngineInput::GetInst()->IsPress("PlayerJump") &&
			(true == GameEngineInput::GetInst()->IsPress("PlayerRight")))
		{
			MovePower.x = Speed;
			Renderer->GetTransform().PixLocalNegativeX();
			StateManager.ChangeState("Jump");
			return;
		}
	}

}

void Player::JumpStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Jump");
	Speed = JumpMoveSpeed;
	MovePower += float4::UP * JumpPower;
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	Gravity(_DeltaTime);

	{
		ColorCheckUpdate();
		ColorCheckUpdateNext(MovePower);

		if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) 
			&& false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)
			&& MovePower.y <= 0)
		{	//�����ߴµ� ����Ű �ȴ����� Idle
			StateManager.ChangeState("Idle");
			MovePower.x = 0.0f;
			return;
		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
		{
			StateManager.ChangeState("Attack");
			return;
		}

		if (true == GameEngineInput::GetInst()->IsPress("SlashBlast"))
		{
			StateManager.ChangeState("SlashBlast1");
			return;
		}

		//���߿� �����ϸ� ���λ����ϴ� ��������
		if (true == GameEngineInput::GetInst()->IsDown("PlayerJump")/* && MyJob == JOB::WARRIOR*/)
		{
			StateManager.ChangeState("SuperJump");
			return;
		}

		if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE) &&
			true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			MovePower = 0.0f;
			Speed = GroundMoveSpeed;
			StateManager.ChangeState("Sadari");
			return;
		}
	}

	NoGravity();
}

void Player::SuperJumpStart(const StateInfo& _Info)
{
	ManaDamage = UseSuperJump;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		//���縶���� �Ҹ� ���������� ���ٸ� �۵����Ѵ�(���߿� �Լ��θ�����)
		return;
	}

	CurMP = CurMP - ManaDamage;

	IsSkill = true;

	Effect->CurAnimationReset();
	Renderer->ChangeFrameAnimation("Jump");
	Speed = GroundMoveSpeed;
	MovePower += (float4::UP * JumpPower * 0.2) + (Dir * SuperJumpPower);
	Effect->On();
}

void Player::SuperJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	//{
	//	//�糡 �Ӹ��κ��� ���� �ε����� �����̴� ���� 0�̵ȴ�
	//	if (false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::WHITE) &&
	//		false == IsColor(COLORCHECKDIR::LEFTTOP, CharacterObject::BLUE))
	//	{
	//		MovePower.x = 0.0f;
	//		stop = true;
	//	}

	//	else
	//	{
	//		//���� �ε����� �ƴ϶�� ��浵 ��������δ�
	//		stop = false;
	//	}
	//}

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE)
		&& false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)
		&& MovePower.y <= 0)
	{	//�����ߴµ� ����Ű �ȴ����� Idle
		StateManager.ChangeState("Idle");
		MovePower.x = 0.0f;
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		StateManager.ChangeState("Attack");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("SlashBlast"))
	{
		StateManager.ChangeState("SlashBlast1");
		return;
	}

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE) &&
		true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		MovePower = 0.0f;
		StateManager.ChangeState("Sadari");
		return;
	}

	NoGravity();
	return;
}

void Player::FallStart(const StateInfo& _Info)
{
	Speed = JumpMoveSpeed;

	Renderer->ChangeFrameAnimation("Jump");
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	
	UpToGround();

	if (true == GameEngineInput::GetInst()->IsPress("PlayerAttack"))
	{
		MovePower.x = 0.0f;
		StateManager.ChangeState("Attack");
		return;
	}

}

void Player::DownJumpStart(const StateInfo& _Info)
{
	if (ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g < 200)
	{
		//200���� �׸����� �۴ٸ� ����
		return;
	}
	PrevColor = ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)];
	Dir = float4::ZERO;
	{
		Renderer->ChangeFrameAnimation("Jump");
		Speed = JumpMoveSpeed;
		//Speed += -75.0f;
		MovePower += float4::UP * (JumpPower * 0.5f);
	}
}
void Player::DownJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//�׶��Ƽ�� �ִ°Ծƴ϶� ���� ����������Ѵ�.
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	Gravity(_DeltaTime);

	//if (300.0f <= abs(MovePower.y))
	//{
	//	//�߶� ���ӵ� �ִ뼳��
	//	MovePower.y = MovePower.y > 0 ? 300.0f : -300.0f;
	//}

	ColorCheckUpdate();

	HitTime += GameEngineTime::GetDeltaTime();
	if (PrevColor.g > ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g &&
		PrevState == "Alert" && Hit == true)
	{
		StateManager.ChangeState("Alert");
		return;
	}

	if (PrevColor.g > ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g)
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::SlashBlast1Start(const StateInfo& _Info)
{
	ManaDamage = UseSlashBlast;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		StateManager.ChangeState("Idle");
		//���縶���� �Ҹ� ���������� ���ٸ� �۵����Ѵ�(���߿� �Լ��θ�����)
		return;
	}

	CurMP = CurMP - ManaDamage;

	IsSkill = true;

	stop = true;

	Renderer->ChangeFrameAnimation("SlashBlast1");
	SlashBlast1->CurAnimationReset();
	SlashBlast1->On();
}
void Player::SlashBlast1Update(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE))
	{
		MovePower.x = 0.0f;
	}

	NoGravity();
	return;
}

void Player::SlashBlast2Start(const StateInfo& _Info)
{
	SlashBlastCollision->On();
	Renderer->ChangeFrameAnimation("SlashBlast2");
	SlashBlast2->CurAnimationReset();
	SlashBlast2->On();
}

void Player::SlashBlast2Update(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE))
	{
		MovePower.x = 0.0f;
	}

	NoGravity();
	return;
}

//==============================================================================//
//==============================================================================//
//=========================��������� ����â=====================================//
//==============================================================================//
//==============================================================================//

void Player::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawSphere(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	//if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	//{	//����ī�޶� ����϶� ī�޶� �÷��̾� �ȿ����̰� ���⼭ ����
	//	return;
	//}

	// ���� üũ�ϰ�
	ColorCheckUpdate();
	StateManager.Update(_DeltaTime);


	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);
	//�翷�� ���� �ƴ϶�� �����δ�
	//GetTransform().SetWorldMove(MovePower * _DeltaTime);

	Dead();
	
	{
		// std::placeholders::_1, std::placeholders::_2 �ϵ��� �־���� �Ѵٴ°��� ���Ű�°�.
		AttackCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterHit, this, std::placeholders::_1, std::placeholders::_2));

		/*SlashBlastCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterSlashBlastHit, this, std::placeholders::_1, std::placeholders::_2));*/
		SlashBlastCollision->IsCollisionEnterBase(CollisionType::CT_OBB2D, 3, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterSlashBlastHit, this, std::placeholders::_1, std::placeholders::_2));

		//Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		//	std::bind(&Player::MonsterCollision, this)
		//);
	}
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Portal, CollisionType::CT_OBB2D,
			std::bind(&Player::PortalCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::PlayerHit, this, std::placeholders::_1, std::placeholders::_2));
	}

	LevelUp();

	if (Hit == true)
	{
		//������������ HitTime����(3���� Idle�� �ٲٱ�����)
		HitTime += _DeltaTime;
	}

	if (CurMP <= 0)
	{
		CurMP = 0;
	}

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

}

bool Player::MonsterHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{	
	//�븻 ����
	
	if (MonsterCount <= 1)
	{
		//�浹�� �Ѹ��� ���ϸ� true
		return true;
	}
	else
	{
		//�� �ܿ� false
		return false;
	}
}

bool Player::MonsterSlashBlastHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (MonsterCount <= 5)
	{
		//�浹�� �ټ����� ���ϸ� true
		return true;
	}
	else
	{
		//�� �ܿ� false
		return false;
	}

	//return true;
}

bool Player::PlayerHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	{
		//�÷��̾� ��¦�ٸ鼭 �ڷ� ����
		Speed = GroundMoveSpeed;
		MovePower += float4::UP * (JumpPower * 0.5f);
		MovePower.x = -Dir.x * Speed;
		Collision->Off();
		Hit = true;
		if (HitTime >= 0.2f)
		{
			StateManager.ChangeState("Idle");
		}
	}

	{
		//������ ���ݷ��� ������ �� ü�¿��� ��
		//StateManager.ChangeState("Alert");
		HitDamage = _Other->GetActor<Monster>()->GetAtt();
		CurHP = CurHP - HitDamage;
		HitCheck = true;
	}
		//����� �Ӹ����� �������(������ �߿伺)
	{
		//�ǰݽ� �� �Ӹ����� ������ ���
		DamageNumber* tmp = _This->GetActor()->GetLevel()->CreateActor<DamageNumber>();
		float4 Pos = _This->GetActor()->GetTransform().GetWorldPosition();
		tmp->GetTransform().SetWorldPosition({ Pos.x,(Pos.y + 32),-400});
		tmp->NumberSetting(HitDamage);
	}
	return true;
}

bool Player::PortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayerUp"))
	{
		PortalOn = true;
		return true;
	}
}

void Player::LevelUp()
{
	if (CurEXP >= EXPMax)
	{
		PlayerLevelUp->CurAnimationReset();
		IsLevelUp = true;

		PlayerLevelUp->On();
		
		PlayerLevel += 1;
		PlayerAtt += 10;
		HPMax += 100;
		CurHP = HPMax;
		MPMax += 50;
		CurMP = MPMax;
		CurEXP = CurEXP - EXPMax;
		EXPMax += 20;
	}
}

void Player::LevelUpEnd()
{
	//������ �ִϸ��̼��� ������ ����
	PlayerLevelUp->Off();
}

void Player::SuperJumpEnd()
{
	//������ �ִϸ��̼��� ������ ����
	Effect->Off();
}

void Player::SlashBlast1End()
{
	SlashBlast1->Off();
	StateManager.ChangeState("SlashBlast2");
}

void Player::SlashBlast2End()
{
	SlashBlastCollision->ResetExData();
	MonsterCount = 0;
	SlashBlast2->Off();
	SlashBlastCollision->Off();
	StateManager.ChangeState("Idle");
	stop = false;
}

void Player::Dead()
{
	if (CurHP <= 0)
	{
		StateManager.ChangeState("Dead");
		Collision->Off();
		stop = true;
		RIP->On();
		MovePower = 0.0f;
	}
}

void Player::UpToGround()
{
	// ���� ���� �����ٸ�.
	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	{	//�����ߴµ� ����Ű �ȴ����� Idle
		StateManager.ChangeState("Idle");

		if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
		{
			MovePower.y = 0.0f;
			while (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE)&&
				   false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::RED))
			{
				GetTransform().SetWorldMove(float4::UP);
				ColorCheckUpdate();
			}
			GetTransform().SetWorldMove(float4::DOWN);
		}

		return;
	}
}

void Player::LevelStartEvent()
{
	if (BeforePlayer != nullptr)
	{
		//���� �̵��Ҷ� ������ �÷��̾� ������
		this->CurHP = BeforePlayer->CurHP;
		this->CurMP = BeforePlayer->CurMP;
		this->HPMax = BeforePlayer->HPMax;
		this->MPMax = BeforePlayer->MPMax;
		this->CurEXP = BeforePlayer->CurEXP;
		this->EXPMax = BeforePlayer->EXPMax;
		this->PlayerLevel = BeforePlayer->PlayerLevel;
		this->PlayerAtt = BeforePlayer->PlayerAtt;
		this->MyJob = BeforePlayer->MyJob;
	}
		MainPlayer = this;
		BeforePlayer = nullptr;
}

void Player::LevelEndEvent()
{
	MainPlayer = nullptr;
	BeforePlayer = this;
}