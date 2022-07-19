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
	: Speed(50.0f)
	, Renderer(nullptr)
{
}

Player::~Player()
{
}

void Test2Start(const FrameAnimation_DESC& _Info)
{
	GameEngineDebug::OutPutString("스타트\n");
}

void Test2End(const FrameAnimation_DESC& _Info)
{
	GameEngineDebug::OutPutString("앤드\n");
}

void Test2Frame(const FrameAnimation_DESC& _Info)
{
	// GameEngineDebug::OutPutString("프레임\n");
}

void Test2Time(const FrameAnimation_DESC& _Info, float _Time)
{
	// GameEngineDebug::OutPutString("타임\n");
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);

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
}