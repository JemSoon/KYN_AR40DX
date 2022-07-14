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
		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->GetTransform().SetLocalScale({ 100, 100, 100 });
		Renderer->SetPipeLine("Color");
		// 내 맴버변수가 아니라 다른객체의 맴버변수를 사용했다면
		// 이건 터질수 있다.
		Renderer->PipeLineHelper.SetConstantBufferLink("ResultColor", Color);
	}
}

void Player::Update(float _DeltaTime)
{
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

	/*if (true == GameEngineInput::GetInst()->IsPress("Rot+"))
	{
		CurRenderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 360.0f * _DeltaTime });
	}
	if (true == GameEngineInput::GetInst()->IsPress("Rot-"))
	{
		CurRenderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, -360.0f * _DeltaTime });
	}*/

	// GlobalContentsValue::Actors::TestMonster

	// ChildRenderer->GetTransform().SetWorldPosition({ 150.0f, 100.0f, 30.0f });

}