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

	//부모 클래스에 적어둠
	//GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Walk", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::PlayerBOT);
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
	Gravity();

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//프리카메라 모드일땐 카메라가 플레이어 안쫓아다니게 여기서 리턴
		return;
	}

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);

		Renderer->GetTransform().PixLocalPositiveX();
		Renderer->ChangeFrameAnimation("Walk");
	}

	if (true == GameEngineInput::GetInst()->IsUp("PlayerLeft"))
	{
		Renderer->ChangeFrameAnimation("Idle");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);

		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->ChangeFrameAnimation("Walk");

	}

	if (true == GameEngineInput::GetInst()->IsUp("PlayerRight"))
	{
		Renderer->ChangeFrameAnimation("Idle");
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

	{	//프리카메라용 임시 조작기
		if (true == GameEngineInput::GetInst()->IsPress("PlayerF"))
		{
			GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("PlayerB"))
		{
			GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
		}
	}

	GroundCheck();

	//카메라가 플레이어 중심으로 쫓아다닌다
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
}