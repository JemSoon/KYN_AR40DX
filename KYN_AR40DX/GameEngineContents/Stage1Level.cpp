#include "Stage1Level.h"
#include "GameEngineCore/GameEngineCameraActor.h"
#include "GameEngineCore/GameEngineCamera.h"
#include "GameEngineCore/GameEngineActor.h"
Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	GameEngineCameraActor* A = CreateActor<GameEngineCameraActor>();
	//PushCamera(A);
	A->CreateComponent<GameEngineCamera>();
}

void Stage1Level::Update(float _DeltaTime)
{
}

void Stage1Level::End()
{
}
