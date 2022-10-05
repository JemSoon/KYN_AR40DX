#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleLogo.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Mouse.h"
#include "Black.h"
TitleLevel::TitleLevel()
	:TitleTime(0.0f)
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

	Open = CreateActor<TitleLogo>(GameObjectGroup::UI);

	B = CreateActor<Black>(OBJECTORDER::Black);
	B->GetTransform().SetWorldPosition({ 0,0,-500 });

	Cursor = CreateActor<Mouse>(OBJECTORDER::UI);
}

void TitleLevel::LevelStartEvent()
{
	TitleTime = 0.0f;

	LevelIn = true;

	GameEngineSound::SoundPlayOneShot("NxLogo.mp3");
	
}

void TitleLevel::Update(float _DeltaTime)
{
	BlackTimeOut();
	//OnEvent();
	TitleTime += _DeltaTime;
	if (true == Open->IsLevelMove)
	{
		GameEngineSound::SoundPlayOneShot("GameIn.mp3");
		GEngine::ChangeLevel("Stage1");
		Open->IsLevelMove = false;
	}

	if (TitleTime >= 4.0f)
	{
		Open->GetLogoRenderer()->Off();

		if (LevelParent::BgmsSwitch == false)
		{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
			LevelParent::BgmPlayer.Stop();
			LevelParent::BgmPlayer = GameEngineSound::SoundPlayControl("Title.mp3");
			LevelParent::BgmPlayer.Volume(0.05f);
			LevelParent::BgmsSwitch = true;
		}
	}

}

void TitleLevel::End()
{
}