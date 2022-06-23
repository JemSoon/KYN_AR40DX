#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
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
	if (false == GameEngineInput::GetInst()->IsKey("CamLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("CamLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("CamRight", 'D');
		GameEngineInput::GetInst()->CreateKey("CamUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("CamDown", 'E');
		GameEngineInput::GetInst()->CreateKey("CamForward", 'W');
		GameEngineInput::GetInst()->CreateKey("CamBack", 'S');
		
		GameEngineInput::GetInst()->CreateKey("CamRotY+", 'R');
		GameEngineInput::GetInst()->CreateKey("CamRotY-", 'T');

	}

	GameEngineCameraActor* A = CreateActor<GameEngineCameraActor>();
	A->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	A->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });


	Player* NewPlayer;

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 300.0f, 0.0f, 0.0f });
		actor->GetTransform().SetWorldScale(float4(50.0f, 50.f, 50.0f));
		actor->SetParent(NewPlayer);
	}
}

void Stage1Level::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress("CamLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CamRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetRightVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamUp"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamDown"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetUpVector() * 100 * _DeltaTime);
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("CamForward"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetForwardVector() * 100 * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamBack"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetForwardVector() * 100 * _DeltaTime);
	}
	
	static float4 Rot = { 0.0f, 0.0f, 0.0f };
	if (true == GameEngineInput::GetInst()->IsPress("CamRotY+"))
	{
		Rot.y += 360.0f * _DeltaTime;
	}
	if (true == GameEngineInput::GetInst()->IsPress("CamRotY-"))
	{
		Rot.y -= 360.0f * _DeltaTime;
	}

	 GetMainCameraActorTransform().SetLocalRotation(Rot);

}

void Stage1Level::End()
{
}
