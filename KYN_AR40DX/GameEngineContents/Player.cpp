#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include "ScoreTestComponent.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
//야매 끌어오기용↓
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>

Player::Player()
	: Speed(100.0f)
	, Renderer(nullptr)
{
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

	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	//ScoreTestComponent* ScoreCom = CreateComponent<ScoreTestComponent>();

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 100 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Walk", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));

		Renderer->ChangeFrameAnimation("Idle");
	}
}

void Player::Update(float _DeltaTime)
{
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
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
		}
	}
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition());

}