#include "PreCompile.h"
#include "Stage2Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "Stage2.h"
#include "Sugar.h"

Stage2Level::Stage2Level()
	: Camera(nullptr)
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
		Stage2* NewMap = CreateActor<Stage2>();
		NewMap->GetPortal()->GetTransform().SetLocalPosition({ 600.0f,-45.0f,-100.0f });
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
{	//레벨이 만들어지고 액터가만들어져서 Player에 만들어두면 레벨에서0으로 설정해도 액터넘어가면서 다시 값이바뀌어서 작동이 안된다. 
	Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition()});

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}

	//카메라 맵밖으로 안나가게(실패?)
	if (0 > Camera->GetTransform().GetLocalPosition().x)
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 0;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));
	}
}

void Stage2Level::End()
{
}
