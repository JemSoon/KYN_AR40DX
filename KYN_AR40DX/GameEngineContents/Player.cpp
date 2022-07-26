#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>


Player::Player()
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

	//�θ� Ŭ������ �����
	//GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 256, 256, 1 });
		Renderer->SetTexture("idle.png");
		//Renderer->ScaleToTexture();//���� ���� �þ��

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Walk", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));

		Renderer->ChangeFrameAnimation("Idle");
	}
}

bool Player::GroundCheck() 
{
	GameEngineTexture* MapTexture = GetLevel<LevelParent>()->GetMap_Col()->GetCurTexture();

	if (nullptr == MapTexture)
	{
		MsgBoxAssert("�浹�� ���� �������� �ʽ��ϴ�");
	}

	
	float4 Color = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == Color.CompareInt4D(float4(1.0f, 1.0f, 1.0f, 0.0f)))
	{
		int a = 0;
	}

	// GetLevel()
	return true;
}

void Player::Update(float _DeltaTime)
{
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

	{	//�߷� �� �ӽ� ���Ʒ� �̵�Ű
		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
		{
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
		}
	}

	{	//����ī�޶�� �ӽ� ���۱�
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

	//ī�޶� �÷��̾� �߽����� �ѾƴٴѴ�
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
}