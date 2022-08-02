#include "PreCompile.h"
#include "Player.h"
#include <GameEngineContents/GlobalContentsValue.h>
#include <iostream>
#include "LevelParent.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
	Speed = 150.0f;
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
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//아직 생성전이라 그런지 쓰면 터짐

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Move", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));
		Renderer->CreateFrameAnimation("Sadari", FrameAnimation_DESC("sadari.png", 0, 1, 0.3f));
		Renderer->CreateFrameAnimation("Jump", FrameAnimation_DESC("jump.png", 0, 0, 0.0f, false));
		Renderer->CreateFrameAnimation("Prone", FrameAnimation_DESC("prone.png", 0, 0, 0.0f, false));
		Renderer->CreateFrameAnimation("Attack", FrameAnimation_DESC("attack2.png", 0, 2, 0.0f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::CUSTOM);
	}
	
	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}


	//GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	//Font->SetText("안녕하세요");


	StateManager.CreateStateMember("Idle", this, &Player::IdleUpdate, &Player::IdleStart);
	StateManager.CreateStateMember("Move", this, &Player::MoveUpdate, &Player::MoveStart);
	StateManager.CreateStateMember("Sadari", this, &Player::SadariUpdate, &Player::SadariStart);
	StateManager.CreateStateMember("Jump", this, &Player::JumpUpdate, &Player::JumpStart);
	StateManager.CreateStateMember("Fall", this, &Player::FallUpdate, &Player::FallStart);
	StateManager.CreateStateMember("Prone", this, &Player::ProneUpdate, &Player::ProneStart);
	StateManager.ChangeState("Idle");

}

void Player::IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Idle");
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		StateManager.ChangeState("Move");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		true == IsNextColor(COLORCHECKDIR::UP, float4::BLUE))
	{
		StateManager.ChangeState("Sadari");
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Prone");
	}
}

void Player::ProneStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Prone");
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);

	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{	//아무것도 안누르고 있고 바닥에있으면 Idle상태로 변경
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		MovePower = GetTransform().GetLeftVector() * Speed * _DeltaTime;

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) &&
			true == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN))
		{	//언덕길은 위로 올리는힘이 추가
			MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
		}

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE)&&
			true == IsNextColor(COLORCHECKDIR::DOWNR, float4::WHITE)&&
			false == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN))
		{	
			StateManager.ChangeState("Fall");
		}
		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		MovePower = GetTransform().GetRightVector() * Speed * _DeltaTime;

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) &&
			true == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))
		{	//언덕길은 위로 올리는힘이 추가
			MovePower += (GetTransform().GetUpVector() * Speed * _DeltaTime);
		}

		if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::WHITE)&&
			true == IsNextColor(COLORCHECKDIR::DOWNL, float4::WHITE)&&
			false == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))
		{	
			StateManager.ChangeState("Fall");
		}
		Renderer->GetTransform().PixLocalNegativeX();
	}


	ColorCheckUpdateNext(MovePower);

	if (false == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN) 
		&& false == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))
	{
		GetTransform().SetWorldMove(MovePower);
	}
	else 
	{
		int a = 0;
	}

	if (true == GameEngineInput::GetInst()->IsDown("PlayerJump"))
	{
		StateManager.ChangeState("Jump");
	}
}

void Player::SadariStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Sadari");
}

void Player::SadariUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MovePower = GetTransform().GetUpVector() * Speed * _DeltaTime;
	GetTransform().SetWorldMove(MovePower);
}

void Player::JumpStart(const StateInfo& _Info)
{
	Dir = float4::ZERO;
	{
		Renderer->ChangeFrameAnimation("Jump");
		//Speed *= 0.5f;
		Speed += -75.0f;
		MovePower += float4::UP * 4.0f;
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{	
	Gravity(_DeltaTime);
	{
		if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
		{	//점프중 오른쪽 이동키 누를시
			MovePower += (float4::RIGHT * _DeltaTime);
			Renderer->GetTransform().PixLocalNegativeX();
		}

		if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
		{	//점프중 왼쪽 이동키 누를시
			MovePower += (float4::LEFT * _DeltaTime);
			Renderer->GetTransform().PixLocalPositiveX();
		}
	}

	GetTransform().SetWorldMove(MovePower);

	if (true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN) && MovePower.y<=0)
	{	//y속도가 마이너스 && 초록 바닥에 닿는다면 = 착지 = idle
		StateManager.ChangeState("Idle");
		Speed = 150.0f;
	}
}

void Player::FallStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Jump");
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Gravity(_DeltaTime);
	if ((true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight"))&&
		true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN))
	{	//착지했는데 방향키 누르고있으면 Move
		StateManager.ChangeState("Move");
	}
	else if ((false == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
			  false == GameEngineInput::GetInst()->IsPress("PlayerRight")) &&
			  true == IsNextColor(COLORCHECKDIR::DOWN, float4::GREEN))
	{	//착지했는데 방향키 안누르면 Idle
		StateManager.ChangeState("Idle");
	}

}

void Player::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//프리카메라 모드일땐 카메라가 플레이어 안움직이게 여기서 리턴
		return;
	}

	// 색깔 체크하고
	ColorCheckUpdate();

	StateManager.Update(_DeltaTime);

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	//카메라가 플레이어 중심으로 쫓아다닌다
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});

	// std::placeholders::_1, std::placeholders::_2 니들이 넣어줘야 한다는것을 명시키는것.
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D,
		std::bind(&Player::MonsterCollision, this, std::placeholders::_1, std::placeholders::_2));


	//Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
	//	std::bind(&Player::MonsterCollision, this)
	//);
}

bool Player::MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{	//플레이어와 몬스터가 충돌하면 해당 몬스터를 죽이고 true 를 리턴
	_Other->GetActor()->Death();

	return true;
}