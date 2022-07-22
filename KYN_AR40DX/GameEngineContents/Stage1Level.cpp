#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "Stage1.h"
#include "Sugar.h"

Stage1Level::Stage1Level()
	: Camera(nullptr)
	, NewPlayer(nullptr)
	
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	{
		Camera = CreateActor<GameEngineCameraActor>();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	}
	
	{
		Stage1* NewMap = CreateActor<Stage1>();
		NewMap->GetPortal()->GetTransform().SetLocalPosition({720.0f,-330.0f,-100.0f});
	}

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetLocalPosition({ 0.0f, -190.0f, 0.0f });
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 300.0f, -5.0f, 100.0f });
	}

	{	
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ -400.0f, -190.0f, 0.0f });
	}
}

void Stage1Level::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	CameraChase();

	NextStage();

	CameraRange();
}

void Stage1Level::End()
{
}

void Stage1Level::CameraChase()
{
	//������ ��������� ���Ͱ���������� Player�� �����θ� ��������0���� �����ص� ���ͳѾ�鼭 �ٽ� ���̹ٲ� �۵��� �ȵȴ�. 
	Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });
}

void Stage1Level::NextStage()
{
	//���� �������� �̵�
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Stage2");
	}
}

void Stage1Level::CameraRange()
{
	//ī�޶� �ʹ����� �ȳ�����
	if (-490 > Camera->GetTransform().GetLocalPosition().x)//���� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = -490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//��ǥ ��� �Լ�
	}

	if (490 < Camera->GetTransform().GetLocalPosition().x)//������ �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (-516 > Camera->GetTransform().GetLocalPosition().y)//y�� �Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = -516;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (100 < Camera->GetTransform().GetLocalPosition().y)//y�� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = 100;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}