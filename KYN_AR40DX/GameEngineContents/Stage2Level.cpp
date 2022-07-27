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
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	{
		Camera = CreateActor<GameEngineCameraActor>();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	}

	{
		Stage = CreateActor<StageObject>();

		Stage->GetMap_Col()->GetTransform().SetLocalScale({1420, 760, 100});
		Stage->GetMap_Col()->SetTexture("stage2_Col.png");

		Stage->GetBG()->GetTransform().SetLocalScale({1420, 760, 100});
		Stage->GetBG()->SetTexture("stage2_BG.png");

		Stage->GetMap()->GetTransform().SetLocalScale({1420, 760, 100});
		Stage->GetMap()->SetTexture("stage2.png");

		Stage->GetPortal()->GetTransform().SetLocalScale({90, 201, 100});
		Stage->GetPortal()->SetTexture("Portal.png");

		Stage->GetPortal()->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
		Stage->GetPortal()->ChangeFrameAnimation("Portal");
		Stage->GetPortal()->GetTransform().SetLocalPosition({ 600.0f,-45.0f,-100.0f });
	}

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetLocalPosition({ -500.0f, -150.0f, 0.0f });
		NewPlayer->GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ -300.0f, -150.0f, 0.0f });
	}

	{
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ -100.0f, 60.0f, 0.0f });
		NPC->GetRenderer()->GetTransform().PixLocalPositiveX();
	}
}

void Stage2Level::Update(float _DeltaTime)
{	
	CameraChase();

	NextStage();

	CameraRange();
}

void Stage2Level::End()
{
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
	//ī�޶� �ʹ����� �ȳ�����(����?)
	if (0 > Camera->GetTransform().GetLocalPosition().x)//���� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 0;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));
	}

	if (70 < Camera->GetTransform().GetLocalPosition().x)//������ ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 70;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (0 > Camera->GetTransform().GetLocalPosition().y)//�Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = 0;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (20 < Camera->GetTransform().GetLocalPosition().y)//�� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = 20;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}