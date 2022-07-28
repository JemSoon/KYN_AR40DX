#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Monster.h"
#include "StageObject.h"
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
	Camera = GetMainCameraActor();
	Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
		GameEngineInput::GetInst()->CreateKey("MapOffSwitch", 'I');
	}
	
	CreateStageObject("Stage1_BG.png", "Stage1_Col.png", "Stage1.png");
	LevelStageObject->GetPortal()->GetTransform().SetLocalPosition({ 100.0f,100.0f,0.0f });

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 1200.0f, -1005.0f, 0.0f });
	}

	{	
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ 700.0f, -980.0f, 0.0f });
	}

	{
		MainUI = CreateActor<Main_HP_MP_UI>(OBJECTORDER::UI);
		MainUI->GetTransform().SetWorldPosition({ 0.0f,-320.0f,0.0f });
	}
}

void Stage1Level::OnEvent()
{
	{
		if (nullptr == Player::GetMainPlayer())
		{
			NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->SetLevelOverOn();
			NewPlayer->GetTransform().SetLocalPosition({ 1070.0f, -1000.0f, 0.0f });
		}
	}

	if (BgmOn == false)
	{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		BgmPlayer.Volume(0.05f);
		BgmOn = true;
	}
}

void Stage1Level::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);//퍼스펙:원근//오서:직교
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	SetMapOnOffSwitch();

	CameraChase();

	NextStage();

	CameraRange();
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
		GEngine::ChangeLevel("Title");
	}
}

void Stage1Level::CameraRange()
{
	float CameraUp = -444.0f/*공중에 붕 뜬 투명배경 포함*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 1630.0f;//2270(전체길이)-640(1280의 절반)

	//카메라 맵밖으로 안나가게
	if (CameraLeft > Camera->GetTransform().GetLocalPosition().x)//왼쪽 끝 막기
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraLeft;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//좌표 출력 함수
	}

	if (CameraRight < Camera->GetTransform().GetLocalPosition().x)//오른쪽 끝 막기
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraRight;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
	//LevelStageObject->GetBG()->GetTransform().GetLocalScale().y
	if (CameraDown > Camera->GetTransform().GetLocalPosition().y)//y축 아래 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraDown;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraUp < Camera->GetTransform().GetLocalPosition().y)//y축 위 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraUp;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}
