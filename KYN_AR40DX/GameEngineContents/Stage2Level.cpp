#include "PreCompile.h"
#include "Stage2Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "Sugar.h"
#include "StageObject.h"

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


	if (false == GameEngineInput::GetInst()->IsKey("MapOffSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("MapOffSwitch", 'I');
	}

}

void Stage2Level::Update(float _DeltaTime)
{	
	if (false == Camera->IsFreeCameraMode())
	{	//����ī�޶� ��尡 �ƴҶ��� ī�޶� �÷��̾ �Ѿƴٴϰ� �� ���� ������ ī�޶� ���ѵȴ�
		CameraChase();
		CameraRange();
	}

	SetMapOnOffSwitch();

	NextStage();
}

void Stage2Level::End()
{
}

void Stage2Level::LevelStartEvent()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Stage2_BG.png", "Stage2_Col.png", "Stage2.png");

	{
		Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
		Portal->GetTransform().SetWorldPosition({ 1285.0f,-428.0f,-10.0f });
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({1000.0f, -500.0f, 0.0f });
	}

	{
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetWorldPosition({ 620.0f, -330.0f, 0.0f });
		NPC->GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	{
		if (nullptr == Player::GetMainPlayer())
		{
			NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();
			NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, -10.0f });
		}

		else if (nullptr == NewPlayer)
		{
			NewPlayer = Player::GetMainPlayer();
			NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, -10.0f });
		}
	}

}

void Stage2Level::CameraChase()
{
	//������ ��������� ���Ͱ���������� Player�� �����θ� ��������0���� �����ص� ���ͳѾ�鼭 �ٽ� ���̹ٲ� �۵��� �ȵȴ�. 
	Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });
}

void Stage2Level::NextStage()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}

void Stage2Level::CameraRange()
{
	float CameraUp = 380.0f/*���߿� �� �� ������ ����*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 780.0f;//2270(��ü����)-640(1280�� ����)
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
}