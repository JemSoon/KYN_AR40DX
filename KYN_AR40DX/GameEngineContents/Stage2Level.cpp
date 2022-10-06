#include "PreCompile.h"
#include "Stage2Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Snail.h"
#include "BossMano.h"
#include "Sugar.h"
#include "StageObject.h"
#include "Inventory.h"
Stage2Level::Stage2Level()
	: Camera(nullptr)
	, NewPlayer(nullptr)

{

}

Stage2Level::~Stage2Level()
{

}

void Stage2Level::Start()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Stage2_BG.png", "Stage2_Col.png", "Stage2.png");
	
	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({200.0f, -500.0f, 0.0f });
	}

	{
		Snail1 = CreateActor<Snail>(OBJECTORDER::Monster);
		Snail1->GetTransform().SetLocalPosition({ 1000.0f, -500.0f, 0.0f });
	}

	{
		Mano = CreateActor<BossMano>(OBJECTORDER::Monster);
		Mano->GetTransform().SetLocalPosition({ 1000.0f, -500.0f, 0.0f });
		Mano->Off();
	}

	{
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetWorldPosition({ 620.0f, -330.0f, 0.0f });
		NPC->GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	{
		Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
		Portal->GetTransform().SetWorldPosition({ 1285.0f,-428.0f, -20.0f });
	}
}

void Stage2Level::Update(float _DeltaTime)
{	
	if (NewPlayer != nullptr)
	{
		//���� ���� �ٽ� ���ƿö� �̹� �÷��̾ �־��ٸ� �޾ƿ´�(������ ������ ü������ �ȴ�)
		NewPlayer = Player::GetMainPlayer();
	}

	if (false == Camera->IsFreeCameraMode())
	{	//����ī�޶� ��尡 �ƴҶ��� ī�޶� �÷��̾ �Ѿƴٴϰ� �� ���� ������ ī�޶� ���ѵȴ�
		CameraChase(_DeltaTime);
		CameraRange();
	}

	BlackTimeOut();

	LevelMove();

	GetMainCamera()->GetProjectionMode();

	MonsterRespawnPosition(Snail1, { 1000.0f, -495.0f, 0.0f });

	//MonsterRespawnPosition(Snail2, { 1201.0f, -1150.0f, 0.0f });
	if (static_cast<int>(NewPlayer->MyJob) == static_cast<int>(JOB::WARRIOR))
	{
		//�����϶� ���� ��
		Mano->On();
	}
}

void Stage2Level::End()
{
}

void Stage2Level::LevelStartEvent()
{
	//if (NewPlayer->PortalOn == false)
	//{
	//	//��Ż�� �̵��Ѱ� �ƴ� GUI�� �̵��ѰŸ� ó���̶� ������ġ 
	//	NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, 0.0f });
	//}

	//if (static_cast<int>(NewPlayer->MyJob) == static_cast<int>(JOB::WARRIOR))
	//{
	//	//�����϶� ���� ��
	//	Mano->On();
	//}
	
	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;
}

void Stage2Level::CameraChase(float _Delta)
{
	//������ ��������� ���Ͱ���������� Player�� �����θ� ��������0���� �����ص� ���ͳѾ�鼭 �ٽ� ���̹ٲ� �۵��� �ȵȴ�. 
	//Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });

	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = { NewPlayer->GetTransform().GetWorldPosition().x,NewPlayer->GetTransform().GetWorldPosition().y,-500 };
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });
}

void Stage2Level::NextStage()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Ship");
	}
}

void Stage2Level::CameraRange()
{
	float CameraUp = 0.0f/*���߿� �� �� ������ ����*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 780.0f;//2270(��ü����)-640(1280�� ����)
	float CameraZ = -500.0f;
	//ī�޶� �ʹ����� �ȳ�����(����?)
	if (CameraLeft > Camera->GetTransform().GetLocalPosition().x)//���� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraLeft;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));
	}

	if (CameraRight < Camera->GetTransform().GetLocalPosition().x)//������ ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraRight;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraDown > Camera->GetTransform().GetLocalPosition().y)//�Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraDown;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraUp < Camera->GetTransform().GetLocalPosition().y)//�� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraUp;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (Camera->GetTransform().GetLocalPosition().z != -500.0f)
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.z = CameraZ;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}

void Stage2Level::LevelMove()
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
			GEngine::ChangeLevel("Ship");
		}
	}
}

void Stage2Level::MonsterRespawnPosition(Monster* _Mob, float4 _Position)
{
	//���Ͱ� ������ ������ ��ġ�� �������ǰԲ� �����صд�
	if (_Mob->DeathCheck == true)
	{
		_Mob->GetTransform().SetLocalPosition(_Position);
	}
}