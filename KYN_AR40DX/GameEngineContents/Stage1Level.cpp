#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	{
		GameEngineCameraActor* A = CreateActor<GameEngineCameraActor>();
		A->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		A->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	}

	Player* NewPlayer;

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 300.0f, -5.0f, 0.0f });
		actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	}
}

void Stage1Level::Update(float _DeltaTime)
{
}

void Stage1Level::End()
{
}
