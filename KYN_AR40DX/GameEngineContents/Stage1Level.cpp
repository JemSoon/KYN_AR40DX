#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "Stage1.h"
Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	{
		GameEngineCameraActor* Camera = CreateActor<GameEngineCameraActor>();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });

		//카메라 맵밖으로 안나가게(실패)
		//if (0 > A->GetTransform().GetLocalPosition().x)
		//{
		//	float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		//	CameraPos.x = 0;
		//	Camera->GetTransform().SetLocalPosition(CameraPos);
		//}
	}
	
	{
		Stage1* NewMap = CreateActor<Stage1>();
		NewMap->GetPortal()->GetTransform().SetLocalPosition({720.0f,-330.0f,-100.0f});
	}

	{
		Player* NewPlayer;
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
