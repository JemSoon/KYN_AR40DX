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

	// ī�޶� ���� ���� ���踦 �� �غ� �ϰ�
	//CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	//CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	
	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0] ���� ���� �ִ�.
	// [0][0][-100][0] �ڷ� ��������

	// ���� ���� ������Ʈ���� ����
	CreateActor<TitleLogo>(GameObjectGroup::UI);
	// [800][0][0][0]
	// [0][400][0][0]
	// [0][0][1][0] ���� ���� �ִ�.
	// [0][200][0][0] �ڷ� ��������
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
		//����ī�޶� �� ����
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	// ���� �ٲ� ���� �ʱ�ȭ
	// GetAccTime();

}

void TitleLevel::End()
{
}