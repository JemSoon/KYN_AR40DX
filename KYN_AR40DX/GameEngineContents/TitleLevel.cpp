#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleLogo.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"

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
	//CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	//CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	
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
}

void TitleLevel::OnEvent()
{
	{
		if (nullptr == Player::GetMainPlayer())
		{
			Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();
			NewPlayer->GetTransform().SetLocalPosition({ 300,-500 });
		}
	}
}

void TitleLevel::Update(float _DeltaTime)
{
	OnEvent();

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Stage1");
	}

	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		//프리카메라 온 오프
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	// 레벨 바뀌어서 오면 초기화
	// GetAccTime();

}

void TitleLevel::End()
{
}