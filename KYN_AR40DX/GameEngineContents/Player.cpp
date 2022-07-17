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
#include <GameEngineCore/GameEngineTextureRenderer.h>

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
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", 'J');
		GameEngineInput::GetInst()->CreateKey("PlayerRight", 'L');
		GameEngineInput::GetInst()->CreateKey("PlayerUp", 'I');
		GameEngineInput::GetInst()->CreateKey("PlayerDown", 'K');
		GameEngineInput::GetInst()->CreateKey("PlayerForward", 'U');
		GameEngineInput::GetInst()->CreateKey("PlayerBack", 'O');
		GameEngineInput::GetInst()->CreateKey("Rot+", VK_NUMPAD0);
		GameEngineInput::GetInst()->CreateKey("Rot-", 'H');
		//넘패드 1번은 노트북 a버튼과 겹친다..
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	ScoreTestComponent* ScoreCom = CreateComponent<ScoreTestComponent>();

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 100, 100, 100 });
		Renderer->SetTexture("Boss_Left.bmp", 0);


		Renderer->CreateFrameAnimation("Test", FrameAnimation_DESC("Boss_Left.bmp", 0, 5, 0.1f));
		Renderer->CreateFrameAnimationFolder("Test2", FrameAnimation_DESC("BlackSet", 0.1f));

		Renderer->AnimationBindTime("Test2", Test2Time);
		Renderer->AnimationBindFrame("Test2", Test2Frame);
		Renderer->AnimationBindStart("Test2", Test2Start);
		Renderer->AnimationBindEnd("Test2", Test2End);

		Renderer->ChangeFrameAnimation("Test");
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