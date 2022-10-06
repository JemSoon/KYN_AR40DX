#include "PreCompile.h"
#include "LevelParent.h"
#include "Perion.h"

#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "Player.h"
#include "Rock.h"
#include "Main_HP_MP_UI.h"
#include "Mouse.h"
#include "Inventory.h"

Perion::Perion()
{

}

Perion::~Perion()
{

}

void Perion::Start()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Perion_BG.png", "Perion_Col.png", "Perion.png");

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({ 885.0f, -410.0f, 0.0f });
	}

	{
		Rock* NPC = CreateActor<Rock>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ 333.0f, -296.0f, 0.0f });
	}

	{
		Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
		Portal->GetTransform().SetWorldPosition({ 888.0f,-400.0f,-450.0f });
	}
}

void Perion::LevelStartEvent()
{
	NewPlayer->GetTransform().SetWorldPosition({ 885.0f, -410.0f, 0.0f });
	
	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;

	if (LevelParent::BgmsSwitch == false)
	{	//������ �ѹ��� ����ǵ��� �ȱ׷��� �����뷡ó�� Ʋ������
		LevelParent::BgmPlayer.Stop();
		LevelParent::BgmPlayer = GameEngineSound::SoundPlayControl("Perion.mp3");
		LevelParent::BgmPlayer.Volume(0.05f);
		LevelParent::BgmsSwitch = true;
	}
}

void Perion::LevelEndEvent()
{
	//���� ������(�Ѿ�� ����)�� �����°�
	LevelParent::BgmsSwitch = false;
}

void Perion::Update(float _DeltaTime)
{
	if (false == Camera->IsFreeCameraMode())
	{	//����ī�޶� ��尡 �ƴҶ��� ī�޶� �÷��̾ �Ѿƴٴϰ� �� ���� ������ ī�޶� ���ѵȴ�
		CameraChase(_DeltaTime);
		CameraRange();
	}

	BlackTimeOut();

	LevelMove();
}

void Perion::End()
{
	
}

void Perion::CameraChase(float _Delta)
{
	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = NewPlayer->GetTransform().GetWorldPosition();
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });
}

void Perion::CameraRange()
{
	float CameraUp = 0.0f/*���߿� �� �� ������ ����*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 640.0f;//1800(��ü����)-640(1280�� ����)

	//ī�޶� �ʹ����� �ȳ�����
	if (CameraLeft > Camera->GetTransform().GetLocalPosition().x)//���� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraLeft;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//��ǥ ��� �Լ�
	}

	if (CameraRight < Camera->GetTransform().GetLocalPosition().x)//������ �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraRight;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
	//LevelStageObject->GetBG()->GetTransform().GetLocalScale().y
	if (CameraDown > Camera->GetTransform().GetLocalPosition().y)//y�� �Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraDown;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraUp < Camera->GetTransform().GetLocalPosition().y)//y�� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraUp;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}

void Perion::LevelMove()
{
	if (NewPlayer->PortalOn == true)
	{
		BlackInTime += GameEngineTime::GetDeltaTime();

		B->GetRenderer()->GetPixelData().MulColor.a += BlackInTime * 0.1f;

		if (B->GetRenderer()->GetPixelData().MulColor.a >= 1.0f)
		{
			B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;
			NewPlayer->PortalOn = false;
			BlackInTime = 0.0f;
			GEngine::ChangeLevel("Stage2");
		}
	}
}