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

	ScoreTestComponent* ScoreCom = CreateComponent<ScoreTestComponent>();

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 100 });


		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.1f));
		//Renderer->CreateFrameAnimationFolder("Test2", FrameAnimation_DESC("BlackSet", 0.1f));

		Renderer->AnimationBindTime("Idle", Test2Time);
		Renderer->AnimationBindFrame("Idle", Test2Frame);
		Renderer->AnimationBindStart("Idle", Test2Start);
		Renderer->AnimationBindEnd("Idle", Test2End);

		Renderer->ChangeFrameAnimation("Idle");
	}
}

void Player::Update(float _DeltaTime)
{
	//static int Frame = 0;
	//static float Time = 0.0f;

	//Time += _DeltaTime;

	//if (0.1f <= Time)
	//{
	//	++Frame;
	//	Renderer->SetFrame(Frame);

	//	if (Frame == 5)
	//	{
	//		Frame = 0;
	//	}

	//	Time -= 0.1f;
	//}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Color.r += 1.0f * _DeltaTime;

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);

		Renderer->ChangeFrameAnimation("Test2");
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerForward"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
	}

}