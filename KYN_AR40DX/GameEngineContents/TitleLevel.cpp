#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleLogo.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	// 카메라를 먼저 만들어서 세계를 볼 준비를 하고
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	//이게 없으니 제대로 안뜬다 이게 뭔지 다른분께 질문해보자↑
	
	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][0][-100][0] 뒤로 물러나서

	// 세상에 보일 오브젝트들을 만들어서
	CreateActor<TitleLogo>(GameObjectGroup::UI);
	// [800][0][0][0]
	// [0][400][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][200][0][0] 뒤로 물러나서

	//Renderer = CreateComponent<GameEngineTextureRenderer>();
	//Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
	//Renderer->SetTexture("LogIn.png", 0);

	TitleLogo* BG;
	BG = CreateActor<TitleLogo>();
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Stage1");
	}

	// 레벨 바뀌어서 오면 초기화
	// GetAccTime();

}

void TitleLevel::End()
{
	int a = 0;
}