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
		Player* NewPlayer;
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
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}

void Stage2Level::End()
{
}
