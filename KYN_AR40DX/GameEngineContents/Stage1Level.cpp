#include "PreCompile.h"
#include "Stage1Level.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
//#include <GameEngineCore/GameEngineBlur.h>	//�����Ŷ��
#include "Player.h"
#include "Snail.h"
#include "StageObject.h"
#include "Sugar.h"
#include "BossMano.h"

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
		// GetMainCamera()->GetCameraRenderTarget()->AddEffect<�����>();

		if (false == GameEngineInput::GetInst()->IsKey("MapOffSwitch"))
		{
			GameEngineInput::GetInst()->CreateKey("MapOffSwitch", 'I');
		}

		CreateStageObject("Stage1_BG.png", "Stage1_Col.png", "Stage1.png");

		{
			Snail* actor1 = CreateActor<Snail>(OBJECTORDER::Monster);
			actor1->GetTransform().SetLocalPosition({ 1200.0f, -1005.0f, 0.0f });
			
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
	}
}

void Stage1Level::LevelStartEvent()
{
	//{
	//	if (nullptr == Player::GetMainPlayer())
	//	{
	//		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	//		//NewPlayer->SetLevelOverOn();
	//		NewPlayer->GetTransform().SetWorldPosition({ 1070.0f, -1000.0f, 0.0f });
	//	}
	//	else if (nullptr == NewPlayer)
	//	{
	//		NewPlayer = Player::GetMainPlayer();
	//		NewPlayer->GetTransform().SetWorldPosition({ 1070.0f, -1000.0f, 0.0f });
	//		//CameraChase(GameEngineTime::GetDeltaTime());
	//	}
	//	else if (nullptr != NewPlayer)
	//	{
	//		//�̹� �� ������� �ִ�==�ٸ��ʿ��� ������
	//		NewPlayer->GetTransform().SetWorldPosition({ 1845, -1240.0f, 0.0f });
	//		//CameraChase(GameEngineTime::GetDeltaTime());
	//	}
	//}

	

	if (BgmOn == false)
	{	//������ �ѹ��� ����ǵ��� �ȱ׷��� �����뷡ó�� Ʋ������
		//BgmPlayer.Stop();
		//BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		//BgmPlayer.Volume(0.05f);
		//BgmOn = true;
	}
	float4 A = Portal->GetTransform().GetWorldPosition();
}

void Stage1Level::Update(float _DeltaTime)
{
	if (false == Camera->IsFreeCameraMode())
	{	//����ī�޶� ��尡 �ƴҶ��� ī�޶� �÷��̾ �Ѿƴٴϰ� �� ���� ������ ī�޶� ���ѵȴ�
		CameraChase(_DeltaTime);
		CameraRange();
	}
	
	SetMapOnOffSwitch();

	NextStage();

	LevelMove();

	float4 A = Camera->GetTransform().GetWorldPosition();
	float4 B = NewPlayer->GetTransform().GetWorldPosition();
	float4 C = Portal->GetTransform().GetWorldPosition();
	int a = 0;
}
void Stage1Level::End()
{
	int a = 0;
}

void Stage1Level::CameraChase(float _Delta)
{
	//������ ��������� ���Ͱ���������� Player�� �����θ� ��������0���� �����ص� ���ͳѾ�鼭 �ٽ� ���̹ٲ� �۵��� �ȵȴ�. 
	//Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });
	float4 f4CurrentPosition = Camera->GetTransform().GetWorldPosition();
	float4 f4DestinationPosition = NewPlayer->GetTransform().GetWorldPosition();
	float4 f4MoveToPosition = float4::Lerp(f4CurrentPosition, f4DestinationPosition, _Delta * 10.f);

	Camera->GetTransform().SetWorldPosition({ f4MoveToPosition.x, f4MoveToPosition.y, -500 });

}

void Stage1Level::NextStage()
{
	//���� �������� �̵�
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}

void Stage1Level::CameraRange()
{
	float CameraUp = -444.0f/*���߿� �� �� ������ ����*/ - 360.0f;
	float CameraDown = (LevelStageObject->GetBG()->GetTransform().GetLocalScale().y - 360.0f) * -1.0f;
	float CameraLeft = 640.0f;
	float CameraRight = 1630.0f;//2270(��ü����)-640(1280�� ����)

	//ī�޶� �ʹ����� �ȳ�����
	if (CameraLeft > Camera->GetTransform().GetLocalPosition().x)//���� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraLeft;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//��ǥ ��� �Լ�
	}

	if (CameraRight < Camera->GetTransform().GetLocalPosition().x)//������ �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = CameraRight;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
	//LevelStageObject->GetBG()->GetTransform().GetLocalScale().y
	if (CameraDown > Camera->GetTransform().GetLocalPosition().y)//y�� �Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = CameraDown;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (CameraUp < Camera->GetTransform().GetLocalPosition().y)//y�� �� ����
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
		NewPlayer->PortalOn = false;
		GEngine::ChangeLevel("Stage2");
	}
}

