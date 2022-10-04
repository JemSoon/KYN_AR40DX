#include "PreCompile.h"
#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Money.h"

#include "Main_HP_MP_UI.h"

#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include "LevelParent.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "DamageNumber.h"
#include "DeadAlert.h"
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
	, UseUpperCharge(20)
	, MyJob(JOB::NONE)
	, ManaDamage(0)
	, FinalAtt(PlayerAtt)
	, AttackCollision(nullptr)
	, SlashBlastCollision(nullptr)
	, GhostActor(nullptr)
	, IsLevelUp(false)
	, SlashBlast1(nullptr)
	, SlashBlast2(nullptr)
	, UpperCharge(nullptr)
	, UpperChargeCollision(nullptr)
	, LeafAttack(nullptr)
	, LeafAttackCollision(nullptr)
	, IsJobChange(false)
	, ItemCount(0)
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
		GameEngineInput::GetInst()->CreateKey("UpperCharge", 'W');
		GameEngineInput::GetInst()->CreateKey("LeafAttack", 'E');
		GameEngineInput::GetInst()->CreateKey("Eat", 'X');
		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		std::vector<unsigned int> Eight = { 0, 1, 2, 3, 4, 5, 6, 7 };
		std::vector<unsigned int> Seven = { 0, 1, 2, 3, 4, 5, 6 };
		std::vector<unsigned int> Six = { 0, 1, 2, 3, 4, 5 };
		std::vector<unsigned int> Five = { 0, 1, 2, 3, 4 };
		std::vector<unsigned int> FourTeen = { 0, 1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10, 11, 12, 13};

		RIP = CreateComponent<GameEngineTextureRenderer>();
		RIP->GetTransform().SetWorldScale({ 128,128,1 });
		RIP->CreateFrameAnimationCutTexture("RIP", FrameAnimation_DESC("RIP.png", Seven, 0.1f, false));
		RIP->ChangeFrameAnimation("RIP");
		RIP->SetPivot(PIVOTMODE::BOT);
		RIP->GetTransform().SetWorldPosition({ 0,-5 });
		RIP->Off();

		{
			//이펙트 슈퍼점프
			Effect = CreateComponent<GameEngineTextureRenderer>();
			Effect->GetTransform().SetWorldScale({ 400,400,1 });
			Effect->GetTransform().SetWorldPosition({ 100,50,0 });
			Effect->CreateFrameAnimationCutTexture("SuperJump", FrameAnimation_DESC("SuperJump.png", Seven, 0.05f, false));
			Effect->ChangeFrameAnimation("SuperJump");
			Effect->Off();
			Effect->AnimationBindEnd("SuperJump", std::bind(&Player::SuperJumpEnd, this));
		}

		{
			//이펙트 슬래시 블라스트
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
			//이팩트 어퍼차지
			UpperCharge = CreateComponent<GameEngineTextureRenderer>();
			UpperCharge->GetTransform().SetWorldScale({ 512,512,1 });
			UpperCharge->GetTransform().SetWorldPosition({ 0,116,-1 });
			UpperCharge->SetPivot(PIVOTMODE::CENTER);
			UpperCharge->CreateFrameAnimationCutTexture("UpperCharge", FrameAnimation_DESC("UppperCharge.png", FourTeen, 0.05f, false));
			UpperCharge->ChangeFrameAnimation("UpperCharge");
			UpperCharge->Off();
			UpperCharge->AnimationBindEnd("UpperCharge", std::bind(&Player::UpperChargeEnd, this));
		}

		{
			//이팩트 리프 어텍
			LeafAttack = CreateComponent<GameEngineTextureRenderer>();
			LeafAttack->GetTransform().SetWorldScale({ 512,512,1 });
			LeafAttack->GetTransform().SetWorldPosition({ -100,32,-1 });
			LeafAttack->SetPivot(PIVOTMODE::CENTER);
			LeafAttack->CreateFrameAnimationCutTexture("LeafAttack", FrameAnimation_DESC("LeafAttack.png", Eight, 0.05f, false));
			LeafAttack->ChangeFrameAnimation("LeafAttack");
			LeafAttack->Off();
			LeafAttack->AnimationBindEnd("LeafAttack", std::bind(&Player::LeafAttackEnd, this));
		}

		{
			GhostActor = GetLevel()->CreateActor<GameEngineActor>();

			GhostActor->SetParent(this);
		}

		{
			Inven = GetLevel()->CreateActor<Inventory>(OBJECTORDER::UI);
			//Inven->CreateInventory(4, 6, { 32,32 ,-470}, 1);
			Inven->GetTransform().SetLocalPosition({ 500,200 });
			Inven->Off();
		}

		Renderer = GhostActor->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->GetTransform().SetLocalPosition({ 100,0,0 });
		Renderer->SetTexture("idle.png");
		
		//Renderer->ScaleToTexture();//아직 생성전이라 그런지 쓰면 터짐

		std::vector<unsigned int> Idle = { 0, 1, 2, 1 };//프레임 골라 실행 테스트
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

		Renderer->CreateFrameAnimationCutTexture("B_Idle", FrameAnimation_DESC("B_idle.png", Idle, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("B_Move", FrameAnimation_DESC("B_walk.png", Three, 0.1f));
		Renderer->CreateFrameAnimationCutTexture("B_Sadari", FrameAnimation_DESC("B_sadari.png", Two, 0.3f));
		Renderer->CreateFrameAnimationCutTexture("B_Jump", FrameAnimation_DESC("B_jump.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("B_Prone", FrameAnimation_DESC("B_prone.png", One, 0.0f, false));
		Renderer->CreateFrameAnimationCutTexture("B_Attack1", FrameAnimation_DESC("B_attack1.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("B_Attack2", FrameAnimation_DESC("B_attack2.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("B_Attack3", FrameAnimation_DESC("B_attack3.png", Three, 0.2f));
		Renderer->CreateFrameAnimationCutTexture("B_Attack4", FrameAnimation_DESC("B_attack4.png", Two, 0.23f));
		Renderer->CreateFrameAnimationCutTexture("B_Alert", FrameAnimation_DESC("B_alert.png", Three, 0.23f));
		Renderer->CreateFrameAnimationCutTexture("SlashBlast1", FrameAnimation_DESC("SlashBlast1p.png", One, 0.01f, false));
		Renderer->CreateFrameAnimationCutTexture("SlashBlast2", FrameAnimation_DESC("SlashBlast2p.png", Two, 0.01f, false));
		Renderer->CreateFrameAnimationCutTexture("UpperCharge", FrameAnimation_DESC("UppperChargep.png", One, 0.01f, false));
		Renderer->CreateFrameAnimationCutTexture("LeafAttack", FrameAnimation_DESC("LeafAttackp.png", Three, 0.01f, false));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::CUSTOM);
	}
	
	{
		Renderer->AnimationBindEnd("Attack1", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack2", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack3", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("Attack4", std::bind(&Player::AttackEnd, this));

		Renderer->AnimationBindEnd("B_Attack1", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("B_Attack2", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("B_Attack3", std::bind(&Player::AttackEnd, this));
		Renderer->AnimationBindEnd("B_Attack4", std::bind(&Player::AttackEnd, this));
	}

	{
		//몸체 콜리전
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{1.0f,0.0f,0.0f,0.3f});
		Collision->GetTransform().SetLocalScale({ 32.0f, 64.0f, 100.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
		Collision->GetTransform().SetWorldPosition({ 0.0f,35.0f });
	}
	{
		//평타 콜리전
		AttackCollision = CreateComponent<GameEngineCollision>();
		AttackCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		AttackCollision->GetTransform().SetLocalScale({ 84.0f, 64.0f, 100.0f });
		AttackCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		AttackCollision->GetTransform().SetWorldPosition({ -35.0f,35.0f });
		//AttackCollision->SetCollisionMode(CollisionMode::Ex);
		AttackCollision->Off();
	}
	{
		//슬래시 블라스트 콜리전
		SlashBlastCollision = CreateComponent<GameEngineCollision>();
		SlashBlastCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,1.0f,0.0f,0.3f });
		SlashBlastCollision->GetTransform().SetLocalScale({ 250.0f, 150.0f, 100.0f });
		SlashBlastCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		SlashBlastCollision->GetTransform().SetWorldPosition({ -125.0f,75.0f });
		SlashBlastCollision->SetCollisionMode(CollisionMode::Ex);
		SlashBlastCollision->Off();
	}
	{
		//어퍼 차지 콜리전
		UpperChargeCollision = CreateComponent<GameEngineCollision>();
		UpperChargeCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,1.0f,0.0f,0.3f });
		UpperChargeCollision->GetTransform().SetLocalScale({ 160.0f, 300.0f, 100.0f });
		UpperChargeCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		UpperChargeCollision->GetTransform().SetWorldPosition({ -64.0f,150.0f });
		UpperChargeCollision->SetCollisionMode(CollisionMode::Ex);
		UpperChargeCollision->Off();
	}
	{
		//리프어택 콜리전
		LeafAttackCollision = CreateComponent<GameEngineCollision>();
		LeafAttackCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,1.0f,0.0f,0.3f });
		LeafAttackCollision->GetTransform().SetLocalScale({ 160.0f, 100.0f, 100.0f });
		LeafAttackCollision->ChangeOrder(OBJECTORDER::PlayerAtt);
		LeafAttackCollision->GetTransform().SetWorldPosition({ -64.0f,32.0f });
		LeafAttackCollision->SetCollisionMode(CollisionMode::Ex);
		LeafAttackCollision->Off();
	}

	//GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	//Font->SetText("12345", "돋움");
	//Font->SetColor({ 0.0f, 0.0f, 0.0f });
	//Font->SetScreenPostion({ 100.0f, 100.0f });

	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::IdleStart, this, std::placeholders::_1));

	int MyValue = 10;//이 밖에있는걸

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
	StateManager.CreateStateMember("UpperCharge"
		, std::bind(&Player::UpperChargeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::UpperChargeStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("LeafAttack"
		, std::bind(&Player::LeafAttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::LeafAttackStart, this, std::placeholders::_1));

	StateManager.ChangeState("Idle");

	JumpPower = 500.0f;
	GravitySpeed = 1500.0f;

	{
		//죽었습니다 안내창
		DieMessage = GetLevel()->CreateActor<DeadAlert>();
		DieMessage->GetTransform().SetWorldPosition({ 0.0f,0.0f,-200.0f });
		DieMessage->Off();
	}
	//블랜드 옵션만 바꾸기위한 코드(미완성)
	//Renderer->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");
}

void Player::DeadStart(const StateInfo& _Info)
{
	if (CurHP <= 0)
	{
		DieMessage->On();
		GameEngineSound::SoundPlayOneShot("Tombstone.mp3", 0, 0.1f);
		CurHP = -9999;
	}
	Hit = false;
	
	CurEXP = CurEXP - (EXPMax * 0.1f);
	//죽으면 전체 EXP에서 10%되는 양을 깐다
	if (CurEXP <= 0)
	{
		CurEXP = 0;
	}

	Renderer->ChangeFrameAnimation("Dead");
}

void Player::DeadUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	{	//공전+자전
		GhostActor->GetTransform().SetAddWorldRotation({ 0,0,_DeltaTime * 100.0f,0 });
		//회전 기준점 설정
		GhostActor->GetTransform().SetWorldPosition({ 0,32,0,0 });
		//렌더러 자전 안함
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
		//평소엔 idle애니메이션
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Idle");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Idle");
		}
	}
	else
	{
		//맞았으면 Alert
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Alert");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Alert");
		}

		Renderer->GetPixelData().MulColor = { 0.3f,0.3f,0.3f,1.0f };
	}
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (IsJobChange == true)
	{
		StateManager.ChangeState("Idle");
		IsJobChange = false;
		return;
	}

	if (HitTime >= 3.0f)
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Idle");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Idle");
		}

		Collision->On();
		Hit = false;
		HitTime = 0.0f;
		Renderer->GetPixelData().MulColor = { 1.0f,1.0f,1.0f,1.0f };
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

	if (true == GameEngineInput::GetInst()->IsPress("UpperCharge"))
	{
		StateManager.ChangeState("UpperCharge");
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

	if (MyJob == JOB::NONE)
	{
		GameEngineSound::SoundPlayOneShot("Attack.mp3");
	}
	else if (MyJob == JOB::WARRIOR)
	{
		GameEngineSound::SoundPlayOneShot("Attack(sword).mp3");
	}

	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

	if (RandomNumber == 1)
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Attack1");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Attack1");
		}
	}
	else if (RandomNumber == 2)
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Attack2");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Attack2");
		}
	}
	else if (RandomNumber == 3)
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Attack3");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Attack3");
		}
	}
	else
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Attack4");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Attack4");
		}
	}


	Speed = GroundMoveSpeed;//어택할때 왠지모르게 스피드가 -75로 변경됨;;
}

void Player::AttackUpdate(float _DeltaTime, const StateInfo& _Info)
{

	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);
	NoGravity();

	{
		//점프하면서 무빙치며 공격할때 방향키 움직이면 계속 움직이면서 공격해서 그거 방지용
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

		if (MyJob == JOB::NONE)
		{
			GameEngineSound::SoundPlayOneShot("Attack.mp3");
		}
		else if (MyJob == JOB::WARRIOR)
		{
			GameEngineSound::SoundPlayOneShot("Attack(sword).mp3");
		}

		int RandomNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

		if (RandomNumber == 1)
		{
			if (MyJob == JOB::NONE)
			{
				Renderer->ChangeFrameAnimation("Attack1");
			}
			if (MyJob == JOB::WARRIOR)
			{
				Renderer->ChangeFrameAnimation("B_Attack1");
			}
		}
		else if (RandomNumber == 2)
		{
			if (MyJob == JOB::NONE)
			{
				Renderer->ChangeFrameAnimation("Attack2");
			}
			if (MyJob == JOB::WARRIOR)
			{
				Renderer->ChangeFrameAnimation("B_Attack2");
			}
		}
		else if (RandomNumber == 3)
		{
			if (MyJob == JOB::NONE)
			{
				Renderer->ChangeFrameAnimation("Attack3");
			}
			if (MyJob == JOB::WARRIOR)
			{
				Renderer->ChangeFrameAnimation("B_Attack3");
			}
		}
		else
		{
			if (MyJob == JOB::NONE)
			{
				Renderer->ChangeFrameAnimation("Attack4");
			}
			if (MyJob == JOB::WARRIOR)
			{
				Renderer->ChangeFrameAnimation("B_Attack4");
			}
		}

		Speed = 150.0f;//어택할때 왠지모르게 스피드가 -75로 변경됨;;
	}
}

void Player::ProneStart(const StateInfo& _Info)
{
	MovePower.y = 0.0f;//가끔 팍 튀는현상 막기용
	if (MyJob == JOB::NONE)
	{
		Renderer->ChangeFrameAnimation("Prone");
	}
	if (MyJob == JOB::WARRIOR)
	{
		Renderer->ChangeFrameAnimation("B_Prone");
	}
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
		//그린200 최종 밑바닥 200바닥은 더 내려가지 몬한다
		StateManager.ChangeState("DownJump");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	Speed = GroundMoveSpeed;
	if (MyJob == JOB::NONE)
	{
		Renderer->ChangeFrameAnimation("Move");
	}
	if (MyJob == JOB::WARRIOR)
	{
		Renderer->ChangeFrameAnimation("B_Move");
	}
	MovePower.y = 0.0f;
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//GameEngineDebug::DrawBox();

	// GameEngineDebug::DebugSphereRender();
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (HitTime >= 3.0f)
	{
		Collision->On();
		Hit = false;
		HitTime = 0.0f;
		Renderer->GetPixelData().MulColor = { 1.0f,1.0f,1.0f,1.0f };
	}

	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{	//아무것도 안누르고 있고 바닥에있으면 Idle상태로 변경
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
		//양 발끝이 화이트라면 Fall상태
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
		//양끝 머리부분이 벽에 부딪히면 움직이는 힘은 0이된다
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
			//벽에 부딪힌게 아니라면 배경도 따라움직인다
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

	if (true == GameEngineInput::GetInst()->IsPress("UpperCharge"))
	{
		StateManager.ChangeState("UpperCharge");
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
			//로컬로 해야 콜리전이 날라가지 않는다
			AttackCollision->GetTransform().SetLocalPosition({ 35.0f,35.0f }); 
			SlashBlastCollision->GetTransform().SetLocalPosition({ 125.0f,75.0f });
			UpperChargeCollision->GetTransform().SetLocalPosition({ 64.0f,150.0f });
			LeafAttackCollision->GetTransform().SetLocalPosition({ 64.0f,32.0f });
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

			UpperCharge->GetTransform().PixLocalNegativeX();
			LeafAttack->GetTransform().PixLocalNegativeX();
			LeafAttack->GetTransform().SetLocalPosition({ 100,32,-1 });
		}
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{	
		Dir = float4::LEFT;
		{
			AttackCollision->GetTransform().SetLocalPosition({ -35.0f,35.0f });
			SlashBlastCollision->GetTransform().SetLocalPosition({ -125.0f,75.0f });
			UpperChargeCollision->GetTransform().SetLocalPosition({ -64.0f,150.0f });
			LeafAttackCollision->GetTransform().SetLocalPosition({ -64.0f,32.0f });
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

			UpperCharge->GetTransform().PixLocalPositiveX();
			LeafAttack->GetTransform().PixLocalPositiveX();
			LeafAttack->GetTransform().SetLocalPosition({ -100,32,-1 });
		}
		return;
	}

}

void Player::SadariStart(const StateInfo& _Info)
{
	if (MyJob == JOB::NONE)
	{
		Renderer->ChangeFrameAnimation("Sadari");
	}
	if (MyJob == JOB::WARRIOR)
	{
		Renderer->ChangeFrameAnimation("B_Sadari");
	}
}

void Player::SadariUpdate(float _DeltaTime, const StateInfo& _Info)
{
	{
		//사다리중 점프시 방향설정용
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
		//사다리중 방향키 눌러서 점프
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
	GameEngineSound::SoundPlayOneShot("Jump.mp3");
	if (MyJob == JOB::NONE)
	{
		Renderer->ChangeFrameAnimation("Jump");
	}
	if (MyJob == JOB::WARRIOR)
	{
		Renderer->ChangeFrameAnimation("B_Jump");
	}
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
		{	//착지했는데 방향키 안누르면 Idle
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

		if (true == GameEngineInput::GetInst()->IsPress("LeafAttack"))
		{
			StateManager.ChangeState("LeafAttack");
			return;
		}

		//나중에 전직하면 따로빼야하는 슈퍼점프
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
	GameEngineSound::SoundPlayOneShot("WarriorLeaf.mp3");
	ManaDamage = UseSuperJump;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		//현재마나사 소모 마나량보다 적다면 작동안한다(나중에 함수로만들자)
		return;
	}

	CurMP = CurMP - ManaDamage;

	IsSkill = true;

	Effect->CurAnimationReset();
	Renderer->ChangeFrameAnimation("B_Jump");
	Speed = GroundMoveSpeed;
	MovePower += (float4::UP * JumpPower * 0.2) + (Dir * SuperJumpPower);
	Effect->On();
}

void Player::SuperJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE)
		&& false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)
		&& MovePower.y <= 0)
	{	//착지했는데 방향키 안누르면 Idle
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

	if (true == GameEngineInput::GetInst()->IsPress("LeafAttack"))
	{
		StateManager.ChangeState("LeafAttack");
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

	if (MyJob == JOB::NONE)
	{
		Renderer->ChangeFrameAnimation("Jump");
	}
	if (MyJob == JOB::WARRIOR)
	{
		Renderer->ChangeFrameAnimation("B_Jump");
	}
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

	if (true == GameEngineInput::GetInst()->IsPress("LeafAttack"))
	{
		StateManager.ChangeState("LeafAttack");
		return;
	}
}

void Player::DownJumpStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("Jump.mp3");
	if (ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)].g < 200)
	{
		//200보다 그린값이 작다면 안함
		return;
	}
	PrevColor = ColorCheck[static_cast<unsigned int>(COLORCHECKDIR::DOWN)];
	Dir = float4::ZERO;
	{
		if (MyJob == JOB::NONE)
		{
			Renderer->ChangeFrameAnimation("Jump");
		}
		if (MyJob == JOB::WARRIOR)
		{
			Renderer->ChangeFrameAnimation("B_Jump");
		}
		Speed = JumpMoveSpeed;
		//Speed += -75.0f;
		MovePower += float4::UP * (JumpPower * 0.5f);
	}
}
void Player::DownJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//그라비티를 주는게아니라 직접 설정해줘야한다.
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	Gravity(_DeltaTime);

	//if (300.0f <= abs(MovePower.y))
	//{
	//	//추락 가속도 최대설정
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
	GameEngineSound::SoundPlayOneShot("SlashBlast.mp3");
	ManaDamage = UseSlashBlast;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		StateManager.ChangeState("Idle");
		//현재마나사 소모 마나량보다 적다면 작동안한다(나중에 함수로만들자)
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

void Player::UpperChargeStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("UpperCharge.mp3");
	ManaDamage = UseUpperCharge;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		StateManager.ChangeState("Idle");
		//현재마나사 소모 마나량보다 적다면 작동안한다(나중에 함수로만들자)
		return;
	}

	CurMP = CurMP - ManaDamage;

	IsSkill = true;

	stop = true;

	Renderer->ChangeFrameAnimation("UpperCharge");
	UpperCharge->CurAnimationReset();
	UpperCharge->On();
	UpperChargeCollision->On();

	Speed = JumpMoveSpeed;
	MovePower += float4::UP * JumpPower * 2.5f;
}

void Player::UpperChargeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (true == GameEngineInput::GetInst()->IsDown("LeafAttack"))
	{
		StateManager.ChangeState("LeafAttack");
		return;
	}

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)
		/*&& MovePower.y <= 0*/)
	{
		MovePower.x = 0.0f;
	}

	NoGravity();
	return;
}

void Player::LeafAttackStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("LeafAttack.mp3");
	ManaDamage = UseUpperCharge;
	if (CurMP < ManaDamage)
	{
		IsSkill = false;
		StateManager.ChangeState("Fall");
		//현재마나사 소모 마나량보다 적다면 작동안한다(나중에 함수로만들자)
		return;
	}

	CurMP = CurMP - ManaDamage;

	IsSkill = true;

	stop = true;

	Renderer->ChangeFrameAnimation("LeafAttack");
	LeafAttack->CurAnimationReset();
	LeafAttack->On();
	LeafAttackCollision->On();
	MovePower.y = 0.0f;
	MovePower += float4::DOWN * JumpPower * 2.5f;
}

void Player::LeafAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	ColorCheckUpdate();
	ColorCheckUpdateNext(MovePower);

	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE) &&
		false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::BLUE)
		/*&& MovePower.y <= 0*/)
	{
		MovePower.x = 0.0f;
	}

	NoGravity();
	return;
}
//==============================================================================//
//==============================================================================//
//=========================여기까지가 상태창=====================================//
//==============================================================================//
//==============================================================================//

void Player::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawSphere(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	//if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	//{	//프리카메라 모드일땐 카메라가 플레이어 안움직이게 여기서 리턴
	//	return;
	//}

	if (true == GameEngineInput::GetInst()->IsDown("Inventory"))
	{
		Inven->OnOffSwitch();
	}

	// 색깔 체크하고
	ColorCheckUpdate();
	StateManager.Update(_DeltaTime);


	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);
	//양옆이 벽이 아니라면 움직인다
	//GetTransform().SetWorldMove(MovePower * _DeltaTime);

	Dead();
	AlertColor();

	{
		// std::placeholders::_1, std::placeholders::_2 니들이 넣어줘야 한다는것을 명시키는것.
		AttackCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterHit, this, std::placeholders::_1, std::placeholders::_2));

		/*SlashBlastCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterSlashBlastHit, this, std::placeholders::_1, std::placeholders::_2));*/
		SlashBlastCollision->IsCollisionEnterBase(CollisionType::CT_OBB2D, 3, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterSlashBlastHit, this, std::placeholders::_1, std::placeholders::_2));

		UpperChargeCollision->IsCollisionEnterBase(CollisionType::CT_OBB2D, 3, CollisionType::CT_OBB2D,
			std::bind(&Player::MonsterUpperChargeHit, this, std::placeholders::_1, std::placeholders::_2));

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
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Money, CollisionType::CT_OBB2D,
			std::bind(&Player::MoneyEatCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Item, CollisionType::CT_OBB2D,
			std::bind(&Player::PotionEatCheck, this, std::placeholders::_1, std::placeholders::_2));
	}

	LevelUp();

	if (Hit == true)
	{
		//맞은순간부터 HitTime진행(3초후 Idle로 바꾸기위해)
		HitTime += _DeltaTime;
	}

	if (CurMP <= 0)
	{
		CurMP = 0;
	}
	
	PlayerRespawn();
	
	GetTransform().SetWorldMove(MovePower * _DeltaTime);
}

bool Player::MonsterHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{	
	//노말 공격
	
	if (MonsterCount <= 1)
	{
		//충돌이 한마리 이하면 true
		return true;
	}
	else
	{
		//그 외엔 false
		return false;
	}
}

bool Player::MonsterSlashBlastHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (MonsterCount <= 6)
	{
		//충돌이 다섯마리 이하면 true
		return true;
	}
	else
	{
		//그 외엔 false
		return false;
	}
}

bool Player::MonsterUpperChargeHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (MonsterCount <= 5)
	{
		//충돌이 다섯마리 이하면 true
		return true;
	}
	else
	{
		//그 외엔 false
		return false;
	}
}

bool Player::MonsterLeafAttackHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (MonsterCount <= 5)
	{
		//충돌이 다섯마리 이하면 true
		return true;
	}
	else
	{
		//그 외엔 false
		return false;
	}
}

bool Player::PlayerHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	{
		//플레이어 폴짝뛰면서 뒤로 후퇴
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
		//몬스터의 공격력을 가져와 내 체력에서 뺌
		//StateManager.ChangeState("Alert");
		HitDamage = _Other->GetActor<Monster>()->GetAtt();
		CurHP = CurHP - HitDamage;
		HitCheck = true;
	}
		//계산후 머리위에 띄워야지(순서의 중요성)
	{
		//피격시 내 머리위에 데미지 띄움
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
		GameEngineSound::SoundPlayOneShot("Portal.mp3");
		PortalOn = true;
		return true;
	}
}

void Player::LevelUp()
{
	if (CurEXP >= EXPMax)
	{
		GameEngineSound::SoundPlayOneShot("LevelUp.mp3",0,0.01f);

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
	//레벨업 애니메이션이 끝나면 끈다
	PlayerLevelUp->Off();
}

void Player::SuperJumpEnd()
{
	//레벨업 애니메이션이 끝나면 끈다
	Effect->Off();
}

void Player::SlashBlast1End()
{
	SlashBlast1->Off();
	StateManager.ChangeState("SlashBlast2");
}

void Player::SlashBlast2End()
{
	MonsterCount = 0;
	SlashBlast2->Off();
	SlashBlastCollision->Off();
	SlashBlastCollision->ResetExData();
	StateManager.ChangeState("Idle");
	stop = false;
}

void Player::Dead()
{
	if (CurHP <= 0 && CurHP>-9999)
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
	// 내가 땅에 박혔다면.
	if (false == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE)&&MovePower.y<=0.0f)
	{	//착지했는데 방향키 안누르면 Idle
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

void Player::PlayerRespawn()
{
	//확인 누를시 부활
	if (DieMessage->IsRespawn == true)
	{
		RIP->Off();
		CurHP = HPMax;
		CurMP = MPMax;
		GhostActor->GetTransform().SetWorldRotation({ 0,0,0,0 });
		GhostActor->GetTransform().SetWorldPosition({ 0,0,0,0 });
		Renderer->GetTransform().SetWorldRotation(float4::ZERO);
		Renderer->GetTransform().SetWorldPosition({ 100,0,0,0 });

		Hit = true;//이걸하면 3초간 무적으로 부활가능

		StateManager.ChangeState("Idle");
		DieMessage->IsRespawn = false;
	}
}

void Player::LevelEndEvent()
{
	MainPlayer = nullptr;
	BeforePlayer = this;
}

void Player::AlertColor()
{
	if (Hit == true)
	{
		if (static_cast<int>(HitTime * 10) % 2 == 0)
		{
			Renderer->GetPixelData().MulColor = { 0.6f,0.6f,0.6f,1.0f };
		}
		if (static_cast<int>(HitTime * 10) % 2 == 1)
		{
			Renderer->GetPixelData().MulColor = { 0.5f,0.5f,0.5f,1.0f };
		}
	}
	if (HitTime >= 3.0f)
	{
		Renderer->GetPixelData().MulColor = { 1.0f,1.0f,1.0f,1.0f };
	}
}

void Player::UpperChargeEnd()
{
	MonsterCount = 0;
	UpperCharge->Off();
	UpperChargeCollision->Off();
	UpperChargeCollision->ResetExData();
	stop = false;
	StateManager.ChangeState("Fall");
}

void Player::LeafAttackEnd()
{
	MonsterCount = 0;
	LeafAttack->Off();
	LeafAttackCollision->Off();
	LeafAttackCollision->ResetExData();
	stop = false;
	StateManager.ChangeState("Idle");
}

bool Player::MoneyEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//인식된게 한개 이하면 줍줍한다
	if (true == GameEngineInput::GetInst()->IsPress("Eat"))
	{
		GameEngineSound::SoundPlayOneShot("PickUpItem.mp3");
		unsigned int a =_Other->GetActor<Money>()->MoneyCost;
		Inven->Money += a;
		_Other->GetActor()->Death();
		return true;
	}
}

bool Player::PotionEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsPress("Eat"))
	{
		GameEngineSound::SoundPlayOneShot("PickUpItem.mp3");
		std::string a = Inven->ItemSlots[5][0]->GetRenderer()->GetCurTexture()->GetNameCopy();
		if (a == "WHITEPOTION.PNG")
		{
			//카운트증가
		}
		else if (a != "NTEST.PNG")
		{
			//배열 다음칸으로
		}
		else
		{
			//해당 배열이 비어있다는것
			Inven->ItemSlots[5][0]->GetRenderer()->SetTexture("WhitePotion.png");
		}

		_Other->GetActor()->Death();
		return true;
	}
}


void Player::LevelStartEvent()
{
	if (BeforePlayer != nullptr)
	{
		//레벨 이동할때 가져갈 플레이어 정보들
		this->CurHP = BeforePlayer->CurHP;
		this->CurMP = BeforePlayer->CurMP;
		this->HPMax = BeforePlayer->HPMax;
		this->MPMax = BeforePlayer->MPMax;
		this->CurEXP = BeforePlayer->CurEXP;
		this->EXPMax = BeforePlayer->EXPMax;
		this->PlayerLevel = BeforePlayer->PlayerLevel;
		this->PlayerAtt = BeforePlayer->PlayerAtt;
		this->MyJob = BeforePlayer->MyJob;
		this->Inven->Money = BeforePlayer->Inven->Money;
		//this->Inven->ItemSlots = BeforePlayer->Inven->ItemSlots;
		//this->BgmPlayer = BeforePlayer->BgmPlayer;
	}
		MainPlayer = this;
		BeforePlayer = nullptr;
}