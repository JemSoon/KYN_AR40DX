#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include "ScoreTestComponent.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
//�߸� ���������
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
		//���е� 1���� ��Ʈ�� a��ư�� ��ģ��..
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });

	ScoreTestComponent* ScoreCom = CreateComponent<ScoreTestComponent>();

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 100, 100, 100 });
		Renderer->SetTexture("Boss_Left.bmp", 5);
	}
}

void Player::Update(float _DeltaTime)
{
	static int Frame = 0;
	static float Time = 0.0f;

	Time += _DeltaTime;

	if (0.1f <= Time)
	{
		++Frame;
		Renderer->SetFrame(Frame);

		if (Frame == 5)
		{
			Frame = 0;
		}

		Time -= 0.1f;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Color.r += 1.0f * _DeltaTime;

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
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