#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>


Player::Player()
	:Color()
{
	Speed = 500.0f;
}

Player::~Player()
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);

		GameEngineInput::GetInst()->CreateKey("PlayerF", 'U');
		GameEngineInput::GetInst()->CreateKey("PlayerB", 'I');
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
		Renderer->SetPivot(PIVOTMODE::PlayerBOT);
	}

	// 무기명 함수를 만들수 있습니다.
	// 이름없는 인스턴스 함수를 만들수가 있습니다.
	// [](const StateInfo& _Info) 
	//{
	//} 람다를 만들겠다 

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

	//if (_Info.StateTime >= 2.0f)
	//{
	//	StateManager.ChangeState("Idle");
	//	return;
	//}
	//

	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerRight") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerUp") &&
		false == GameEngineInput::GetInst()->IsPress("PlayerDown") &&
		true ==GroundCheck())
	{	//아무것도 안누르고 있고 바닥에있으면 Idle상태로 변경
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);

		Renderer->GetTransform().PixLocalPositiveX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);

		Renderer->GetTransform().PixLocalNegativeX();
		//Renderer->ChangeFrameAnimation("Walk");

	}

	{	//중력 전 임시 위아래 이동키
		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
		{
			if (true == Color.CompareInt4D(float4(0.0f, 1.0f, 0.0f, 1.0f))/*||
				true == Color.CompareInt4D(float4(0.0f, 0.0f, 1.0f, 1.0f))*/)
			{	//빨강이나 초록에 부딪히면 y움직임은 0이된다
				GetTransform().SetWorldMove(GetTransform().GetDownVector() * 0 * _DeltaTime);
				return;
			}
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
		}
	}

}

bool Player::GroundCheck() 
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("충돌용 맵이 존재하지 않습니다");
	}

	//컬러충돌용 체크 점
	Color = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == Color.CompareInt4D(float4(1.0f, 1.0f, 1.0f, 0.0f)))
	{	//BGRA
		//투명 배경색이 아니라면
		//빨간색 혹은 초록색 땅에 부딪혔다
		int a = 0;
	}

	// GetLevel()
	return true;
}

void Player::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//프리카메라 모드일땐 카메라가 플레이어 안쫓아다니게 여기서 리턴
		return;
	}

	Gravity();
	GroundCheck();
	StateManager.Update(_DeltaTime);

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	


	//카메라가 플레이어 중심으로 쫓아다닌다
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
}