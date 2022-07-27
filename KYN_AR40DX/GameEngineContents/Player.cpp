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
		//Renderer->ScaleToTexture();//���� �������̶� �׷��� ���� ����

		Renderer->CreateFrameAnimation("Idle", FrameAnimation_DESC("idle.png", 0, 2, 0.3f));
		Renderer->CreateFrameAnimation("Move", FrameAnimation_DESC("walk.png", 0, 3, 0.1f));

		Renderer->ChangeFrameAnimation("Idle");
		Renderer->SetPivot(PIVOTMODE::PlayerBOT);
	}

	// ����� �Լ��� ����� �ֽ��ϴ�.
	// �̸����� �ν��Ͻ� �Լ��� ������� �ֽ��ϴ�.
	// [](const StateInfo& _Info) 
	//{
	//} ���ٸ� ����ڴ� 

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
	{	//�ƹ��͵� �ȴ����� �ְ� �ٴڿ������� Idle���·� ����
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

	{	//�߷� �� �ӽ� ���Ʒ� �̵�Ű
		if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
		{
			GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
		{
			if (true == Color.CompareInt4D(float4(0.0f, 1.0f, 0.0f, 1.0f))/*||
				true == Color.CompareInt4D(float4(0.0f, 0.0f, 1.0f, 1.0f))*/)
			{	//�����̳� �ʷϿ� �ε����� y�������� 0�̵ȴ�
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
		MsgBoxAssert("�浹�� ���� �������� �ʽ��ϴ�");
	}

	//�÷��浹�� üũ ��
	Color = MapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (false == Color.CompareInt4D(float4(1.0f, 1.0f, 1.0f, 0.0f)))
	{	//BGRA
		//���� ������ �ƴ϶��
		//������ Ȥ�� �ʷϻ� ���� �ε�����
		int a = 0;
	}

	// GetLevel()
	return true;
}

void Player::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{	//����ī�޶� ����϶� ī�޶� �÷��̾� ���Ѿƴٴϰ� ���⼭ ����
		return;
	}

	Gravity();
	GroundCheck();
	StateManager.Update(_DeltaTime);

	{
		float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();

		float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition(); 
	}

	


	//ī�޶� �÷��̾� �߽����� �ѾƴٴѴ�
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition()});
}