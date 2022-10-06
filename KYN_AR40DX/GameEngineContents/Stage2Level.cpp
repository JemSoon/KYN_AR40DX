#include "PreCompile.h"
#include "Stage2Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Snail.h"
#include "BossMano.h"
#include "Sugar.h"
#include "StageObject.h"
#include "Inventory.h"
Stage2Level::Stage2Level()
	: Camera(nullptr)
	, NewPlayer(nullptr)

{

}

Stage2Level::~Stage2Level()
{

}

void Stage2Level::Start()
{
	{
		Camera = GetMainCameraActor();
		Camera->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		Camera->GetTransform().SetWorldPosition({ 0,0,-500.0f });
	}

	CreateStageObject("Stage2_BG.png", "Stage2_Col.png", "Stage2.png");
	
	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({200.0f, -500.0f, 0.0f });
	}

	{
		Snail1 = CreateActor<Snail>(OBJECTORDER::Monster);
		Snail1->GetTransform().SetLocalPosition({ 1000.0f, -500.0f, 0.0f });
	}

	{
		Mano = CreateActor<BossMano>(OBJECTORDER::Monster);
		Mano->GetTransform().SetLocalPosition({ 1000.0f, -500.0f, 0.0f });
		Mano->Off();
	}

	{
		Sugar* NPC = CreateActor<Sugar>(OBJECTORDER::NPC);
		NPC->GetTransform().SetWorldPosition({ 620.0f, -330.0f, 0.0f });
		NPC->GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	{
		Portal = CreateActor<PortalObject>(OBJECTORDER::Portal);
		Portal->GetTransform().SetWorldPosition({ 1285.0f,-428.0f, -20.0f });
	}
}

void Stage2Level::Update(float _DeltaTime)
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

	LevelMove();

	GetMainCamera()->GetProjectionMode();

	MonsterRespawnPosition(Snail1, { 1000.0f, -495.0f, 0.0f });

	//MonsterRespawnPosition(Snail2, { 1201.0f, -1150.0f, 0.0f });
	if (static_cast<int>(NewPlayer->MyJob) == static_cast<int>(JOB::WARRIOR))
	{
		//전사일때 마노 젠
		Mano->On();
	}
}

void Stage2Level::End()
{
}

void Stage2Level::LevelStartEvent()
{
	//if (NewPlayer->PortalOn == false)
	//{
	//	//포탈로 이동한게 아닌 GUI로 이동한거면 처음이랑 같은위치 
	//	NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, 0.0f });
	//}

	//if (static_cast<int>(NewPlayer->MyJob) == static_cast<int>(JOB::WARRIOR))
	//{
	//	//전사일때 마노 젠
	//	Mano->On();
	//}
	
	BlackOutTime = 0.0f;

	LevelIn = true;

	B->GetRenderer()->GetPixelData().MulColor.a = 1.0f;
}

void Stage2Level::CameraChase(float _Delta)
{
	//레벨이 만들어지고 액터가만들어져서 Player에 만들어두면 레벨에서0으로 설정해도 액터넘어가면서 다시 값이바뀌어서 작동이 안된다. 
	//Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });

	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = { NewPlayer->GetTransform().GetWorldPosition().x,NewPlayer->GetTransform().GetWorldPosition().y,-500 };
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });
}

void Stage2Level::NextStage()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Ship");
	}
}

void Stage2Level::CameraRange()
{
	float CameraUp = 0.0f/*공중에 붕 뜬 투명배경 포함*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 780.0f;//2270(전체길이)-640(1280의 절반)
	float CameraZ = -500.0f;
	//카메라 맵밖으로 안나가게(실패?)
	if (CameraLeft > Camera->GetTransform().GetLocalPosition().x)//왼쪽 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraLeft;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));
	}

	if (CameraRight < Camera->GetTransform().GetLocalPosition().x)//오른쪽 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraRight;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraDown > Camera->GetTransform().GetLocalPosition().y)//아래 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraDown;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraUp < Camera->GetTransform().GetLocalPosition().y)//위 고정
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraUp;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (Camera->GetTransform().GetLocalPosition().z != -500.0f)
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.z = CameraZ;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}

void Stage2Level::LevelMove()
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
			GEngine::ChangeLevel("Ship");
		}
	}
}

void Stage2Level::MonsterRespawnPosition(Monster* _Mob, float4 _Position)
{
	//몬스터가 죽으면 지정한 위치에 리스폰되게끔 세팅해둔다
	if (_Mob->DeathCheck == true)
	{
		_Mob->GetTransform().SetLocalPosition(_Position);
	}
}