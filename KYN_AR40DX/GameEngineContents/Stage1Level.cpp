#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "Stage1.h"
#include "Sugar.h"
#include "Main_HP_MP_UI.h"

Stage1Level::Stage1Level()
	: Camera(nullptr)
	, NewPlayer(nullptr)
	, BgmPlayer()
	, BgmOn(false)
	
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	{
		Camera = CreateActor<GameEngineCameraActor>();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	}
	
	{
		Stage1* NewMap = CreateActor<Stage1>();
		NewMap->GetPortal()->GetTransform().SetLocalPosition({720.0f,-330.0f,0.0f});
	}

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetLocalPosition({ 0.0f, -190.0f, 0.0f });
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 300.0f, -5.0f, 0.0f });
	}

	{	
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ -400.0f, -190.0f, 0.0f });
	}

	{
		MainUI = CreateActor<Main_HP_MP_UI>(OBJECTORDER::UI);
		MainUI->GetTransform().SetWorldPosition({ 0.0f,-320.0f,0.0f });
		MainUI->SetParent(Camera);
	}
}

void Stage1Level::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);//퍼스펙:원근//오서:직교
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	OnEvent();

	//CameraChase();

	NextStage();

	//CameraRange();
}

void Stage1Level::End()
{
}

void Stage1Level::CameraChase()
{
	//레벨이 만들어지고 액터가만들어져서 Player에 만들어두면 레벨에서0으로 설정해도 액터넘어가면서 다시 값이바뀌어서 작동이 안된다. 
	Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });

}

void Stage1Level::NextStage()
{
	//다음 스테이지 이동
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Stage2");
	}
}

void Stage1Level::CameraRange()
{
	//카메라 맵밖으로 안나가게
	if (-490 > Camera->GetTransform().GetLocalPosition().x)//왼쪽 끝 막기
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = -490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//좌표 출력 함수
	}

	if (490 < Camera->GetTransform().GetLocalPosition().x)//오른쪽 끝 막기
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (-516 > Camera->GetTransform().GetLocalPosition().y)//y축 아래 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = -516;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (100 < Camera->GetTransform().GetLocalPosition().y)//y축 위 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = 100;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}

void Stage1Level::OnEvent()
{
	if (BgmOn == false)
	{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		BgmPlayer.Volume(0.1f);
		BgmOn = true;
	}
}
