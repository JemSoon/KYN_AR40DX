#include "PreCompile.h"
#include "Stage2Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Snail.h"
#include "Sugar.h"
#include "StageObject.h"

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

	if (false == GameEngineInput::GetInst()->IsKey("MapOffSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("MapOffSwitch", 'I');
	}

	CreateStageObject("Stage2_BG.png", "Stage2_Col.png", "Stage2.png");
	
	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		NewPlayer->GetTransform().SetWorldPosition({ 1070.0f, -1000.0f, 0.0f });
	}

	{
		Snail* actor = CreateActor<Snail>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 1000.0f, -500.0f, 0.0f });
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
	//if (false == Camera->IsFreeCameraMode())
	{	//프리카메라 모드가 아닐때만 카메라가 플레이어를 쫓아다니고 맵 범위 안으로 카메라가 제한된다
		CameraChase(_DeltaTime);
		CameraRange();
	}

	SetMapOnOffSwitch();

	NextStage();

	float4 A = Camera->GetTransform().GetWorldPosition();
	float4 B = NewPlayer->GetTransform().GetWorldPosition();
	float4 C = Portal->GetTransform().GetWorldPosition();
	int a = 0;

	GetMainCamera()->GetProjectionMode();
}

void Stage2Level::End()
{
}

void Stage2Level::LevelStartEvent()
{
	//{
	//	if (nullptr == Player::GetMainPlayer())
	//	{
	//		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	//		NewPlayer->SetLevelOverOn();
	//		NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, 0.0f });
	//	}

	//	else if (nullptr == NewPlayer)
	//	{
	//		NewPlayer = Player::GetMainPlayer();
	//		NewPlayer->GetTransform().SetWorldPosition({ 200.0f, -500.0f, 0.0f });
	//		//CameraChase(GameEngineTime::GetDeltaTime());
	//	}

	//	else if (nullptr != NewPlayer)
	//	{
	//		//이미 다 만들어져 있다==다른맵에서 왔을때(얘는 왜 z값 앞으로 안땡겨주면 사라짐?)
	//		//NewPlayer->GetTransform().SetWorldPosition({ 100, -500.0f, 0.0f });
	//		//CameraChase(GameEngineTime::GetDeltaTime());
	//	}

	//	//Camera->GetTransform().SetWorldPosition({ -300,-800,-500 });
	//}
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
		GEngine::ChangeLevel("Title");
	}
}

void Stage2Level::CameraRange()
{
	float CameraUp = 380.0f/*공중에 붕 뜬 투명배경 포함*/ - 360.0f;
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