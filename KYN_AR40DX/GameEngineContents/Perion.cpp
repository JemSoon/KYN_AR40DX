#include "PreCompile.h"
#include "LevelParent.h"
#include "Perion.h"

#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "Player.h"
#include "Rock.h"
#include "Main_HP_MP_UI.h"
#include "Mouse.h"
#include "Inventory.h"

Perion::Perion()
{

}

Perion::~Perion()
{

}

void Perion::Start()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Perion_BG.png", "Perion_Col.png", "Perion.png");

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({ 885.0f, -410.0f, 0.0f });
	}

	{
		Rock* NPC = CreateActor<Rock>(OBJECTORDER::NPC);
		NPC->GetTransform().SetLocalPosition({ 333.0f, -296.0f, 0.0f });
	}

	{
		Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
		Portal->GetTransform().SetWorldPosition({ 888.0f,-400.0f,-450.0f });
	}
}

void Perion::LevelStartEvent()
{
	NewPlayer->GetTransform().SetWorldPosition({ 885.0f, -410.0f, 0.0f });
	
	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;

	if (LevelParent::BgmsSwitch == false)
	{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
		LevelParent::BgmPlayer.Stop();
		LevelParent::BgmPlayer = GameEngineSound::SoundPlayControl("Perion.mp3");
		LevelParent::BgmPlayer.Volume(0.05f);
		LevelParent::BgmsSwitch = true;
	}
}

void Perion::LevelEndEvent()
{
	//레벨 마지막(넘어가기 직전)에 들어오는거
	LevelParent::BgmsSwitch = false;
}

void Perion::Update(float _DeltaTime)
{
	if (false == Camera->IsFreeCameraMode())
	{	//프리카메라 모드가 아닐때만 카메라가 플레이어를 쫓아다니고 맵 범위 안으로 카메라가 제한된다
		CameraChase(_DeltaTime);
		CameraRange();
	}

	BlackTimeOut();

	LevelMove();
}

void Perion::End()
{
	
}

void Perion::CameraChase(float _Delta)
{
	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = NewPlayer->GetTransform().GetWorldPosition();
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });
}

void Perion::CameraRange()
{
	float CameraUp = 0.0f/*공중에 붕 뜬 투명배경 포함*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 640.0f;//1800(전체길이)-640(1280의 절반)

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

void Perion::LevelMove()
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