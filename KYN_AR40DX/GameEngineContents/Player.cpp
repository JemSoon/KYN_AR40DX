#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include "LevelParent.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
	Speed = 500.0f;
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
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//아직 생성전이라 그런지 쓰면 터짐

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Move", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::CUSTOM);
		Renderer->GetTransform().SetLocalPosition({0.0f, 45.0f});
	}

	StateManager.CreateStateMember("Idle", this, &Player::IdleUpdate, &Player::IdleStart);
	StateManager.CreateStateMember("Move", this, &Player::MoveUpdate, &Player::MoveStart);
	StateManager.ChangeState("Idle");

}

void Player::IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Idle");
}
void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerRight") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerUp") ||
		true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Move");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{	//아무것도 안누르고 있고 바닥에있으면 Idle상태로 변경
		StateManager.ChangeState("Idle");
		return;
	}

	float4 Dir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Dir = GetTransform().GetLeftVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		Dir = GetTransform().GetRightVector() * Speed * _DeltaTime;
		Renderer->GetTransform().PixLocalNegativeX();
	}

	ColorCheckUpdateNext(Dir);

	if (false == IsNextColor(COLORCHECKDIR::LEFT, float4::GREEN) 
		&& false == IsNextColor(COLORCHECKDIR::RIGHT, float4::GREEN))
	{
		GetTransform().SetWorldMove(Dir);
	}
	else {
		int a = 0;
	}
}

void Player::Update(float _DeltaTime)
{
	// GetTransform().SetWorldMove(float4::DOWN * 100.0f * _DeltaTime);


	if (_DeltaTime >= 0.1f)
	{
		_DeltaTime = 0.0f;
	}

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//프리카메라 모드일땐 카메라가 플레이어 안움직이게 여기서 리턴
		return;
	}

	// 색깔 체크하고
	ColorCheckUpdate();

	Gravity(_DeltaTime);
	//GroundCheck();
	StateManager.Update(_DeltaTime);

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	//카메라가 플레이어 중심으로 쫓아다닌다
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
}