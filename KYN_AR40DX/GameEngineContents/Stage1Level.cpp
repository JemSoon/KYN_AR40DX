#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
//#include <GameEngineCore/GameEngineBlur.h>	//블러쓸거라면
#include "Player.h"
#include "Snail.h"
#include "StageObject.h"
#include "Sugar.h"
#include "BossMano.h"

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
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
		

		//GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		//GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
		// GetMainCamera()->GetCameraRenderTarget()->AddEffect<디스토션>();

		CreateStageObject("Stage1_BG.png", "Stage1_Col.png", "Stage1.png");

		MainUI = CreateActor<Main_HP_MP_UI>(OBJECTORDER::UI);
		MainUI->GetTransform().SetWorldPosition({ 0.0f,-320.0f,-100.0f });
		MainUI->SetLevelOverOn();


		{
			Snail1 = CreateActor<Snail>(OBJECTORDER::Monster);
			Snail1->GetTransform().SetLocalPosition({ 1200.0f, -1005.0f, 0.0f });
			
			Snail* actor2 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor2->GetTransform().SetLocalPosition({ 1201.0f, -1005.0f, 0.0f });
			
			Snail* actor3 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor3->GetTransform().SetLocalPosition({ 1202.0f, -1005.0f, 0.0f });
			
			Snail* actor4 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor4->GetTransform().SetLocalPosition({ 1203.0f, -1005.0f, 0.0f });
			
			Snail* actor5 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor5->GetTransform().SetLocalPosition({ 1204.0f, -1005.0f, 0.0f });
			
			Snail* actor6 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor6->GetTransform().SetLocalPosition({ 1205.0f, -1005.0f, 0.0f });
			
			//Mano = CreateActor<BossMano>(OBJECTORDER::Monster);
			//Mano->GetTransform().SetLocalPosition({ 1100.0f, -1005.0f, 0.0f });
		}

		{
			Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
			NPC->GetTransform().SetLocalPosition({ 700.0f, -980.0f, 0.0f });
		}

		{
			Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
			Portal->GetTransform().SetWorldPosition({ 1853.0f,-1235.0f,-450.0f });
		}

		{
			NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
			NewPlayer->GetTransform().SetWorldPosition({ 1070.0f, -1000.0f, 0.0f });
		}

		{
			//WPotion = CreateActor<Potion>(OBJECTORDER::Item);
			//WPotion->GetTransform().SetWorldPosition({ 1070.0f, -1000.0f, 0.0f });
		}
	}
}

void Stage1Level::LevelStartEvent()
{
	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;

	if (BgmOn == false)
	{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
		//BgmPlayer.Stop();
		//BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		//BgmPlayer.Volume(0.05f);
		//BgmOn = true;
	}
	
}

void Stage1Level::Update(float _DeltaTime)
{
	if (false == Camera->IsFreeCameraMode())
	{	//프리카메라 모드가 아닐때만 카메라가 플레이어를 쫓아다니고 맵 범위 안으로 카메라가 제한된다
		CameraChase(_DeltaTime);
		CameraRange();
	}

	BlackTimeOut();

	LevelMove();

	//MonsterRespawnPosition(Snail1, { 600,-1150,0 });
}
void Stage1Level::End()
{
	int a = 0;
}

void Stage1Level::CameraChase(float _Delta)
{
	//레벨이 만들어지고 액터가만들어져서 Player에 만들어두면 레벨에서0으로 설정해도 액터넘어가면서 다시 값이바뀌어서 작동이 안된다. 
	//Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });
	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = NewPlayer->GetTransform().GetWorldPosition();
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });

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

void Stage1Level::LevelMove()
{
	if (NewPlayer->PortalOn == true)
	{
		BlackInTime += GameEngineTime::GetDeltaTime();

		B->GetRenderer()->GetPixelData().MulColor.a += BlackInTime * 0.1f;

		if (B->GetRenderer()->GetPixelData().MulColor.a >= 1.0f)
		{
			B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;
			NewPlayer->PortalOn = false;
			BlackInTime = 0.0f;
			GEngine::ChangeLevel("Stage2");
		}
	}
}

void Stage1Level::MonsterRespawnPosition(Monster* _Mob, float4 _Position)
{
	//몬스터가 죽으면 지정한 위치에 리스폰되게끔 세팅해둔다
	if (_Mob->DeathCheck == true)
	{
		_Mob->GetTransform().SetLocalPosition(_Position);
	}
}