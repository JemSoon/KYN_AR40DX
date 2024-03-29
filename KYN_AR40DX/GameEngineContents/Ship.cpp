#include "PreCompile.h"
#include "LevelParent.h"
#include "Ship.h"

#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

#include "Player.h"
#include "Main_HP_MP_UI.h"
#include "Mouse.h"
#include "Inventory.h"
#include "Stage1Level.h"

Ship::Ship()
	: Camera(nullptr)
	, NewPlayer(nullptr)
	, BgmPlayer()
	, BgmOn(false)
	, ShipTime(0.0f)
{

}

Ship::~Ship()
{
}


void Ship::Start()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Ship_BG.png", "Ship_Col.png", "Ship1.png");

	LevelStageObject->GetMap()->GetTransform().SetWorldPosition({ 0,0,-100 });
	LevelStageObject->GetBG()->GetTransform().SetWorldPosition({ 0,-100,0 });
	LevelStageObject->GetBG()->SetPivot(PIVOTMODE::LEFTTOP);

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({ 950.0f, -1200.0f, 0.0f });
	}

	LevelStageObject->GetMap()->CreateFrameAnimationFolder("Ship", FrameAnimation_DESC("Ship", 0.1f));
	LevelStageObject->GetMap()->ChangeFrameAnimation("Ship");
}

void Ship::Update(float _DeltaTime)
{
	if (NewPlayer != nullptr)
	{
		//만약 레벨 다시 돌아올때 이미 플레이어가 있었다면 받아온다(전직후 렌더러 체인지가 안댐)
		NewPlayer = Player::GetMainPlayer();
	}

	if (false == Camera->IsFreeCameraMode())
	{	//프리카메라 모드가 아닐때만 카메라가 플레이어를 쫓아다니고 맵 범위 안으로 카메라가 제한된다
		CameraChase(_DeltaTime);
		CameraRange();
	}

	BlackTimeOut();

	ShipTime += _DeltaTime;

	LevelStageObject->GetBG()->GetTransform().SetWorldPosition({ -(ShipTime*50.0f),-100,0});
	LevelMove();
}

void Ship::End()
{
}

void Ship::CameraChase(float _Delta)
{
	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = NewPlayer->GetTransform().GetWorldPosition();
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });
}

void Ship::LevelStartEvent()
{
	if (NewPlayer->PortalOn == false)
	{
		//포탈로 이동한게 아닌 GUI로 이동한거면 처음이랑 같은위치 
		NewPlayer->GetTransform().SetWorldPosition({ 950.0f, -1200.0f, 0.0f });
	}

	BgmOn = false;

	ShipTime = 0.0f;

	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;

	if (LevelParent::BgmsSwitch == true)
	{	//음악이 한번만 실행되도록 안그러면 돌림노래처럼 틀어진다
		LevelParent::BgmPlayer.Stop();
		LevelParent::BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		LevelParent::BgmPlayer.Volume(0.05f);
		LevelParent::BgmsSwitch = false;
	}
}

void Ship::LevelMove()
{
	if (ShipTime >= 10.0f)
	{
		BlackInTime += GameEngineTime::GetDeltaTime();

		B->GetRenderer()->GetPixelData().MulColor.a += BlackInTime * 0.1f;

		if (B->GetRenderer()->GetPixelData().MulColor.a >= 1.0f)
		{
			B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;
			GEngine::ChangeLevel("Perion");
		}
	}
}

void Ship::CameraRange()
{
	float CameraUp = -444.0f/*공중에 붕 뜬 투명배경 포함*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 1160.0f;//1800(전체길이)-640(1280의 절반)

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