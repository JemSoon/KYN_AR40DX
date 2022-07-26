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
		Stage = CreateActor<StageObject>();
		
		{	//�÷��浹 ��
			Stage->GetMap_Col()->GetTransform().SetLocalScale({ 2270, 1807, 100 });
			Stage->GetMap_Col()->SetTexture("Stage1_Col.png");

			//�޹��	�긦 ī�޶��̵� ������ 1������ ������ �Ѿƿ��� �ϰ� �ʹ�..
			Stage->GetBG()->GetTransform().SetLocalScale({4270, 1807, 100});
			Stage->GetBG()->SetTexture("Stage1_BG.png");
		}

		{	//��¥ �׸� ��
			Stage->GetMap()->GetTransform().SetLocalScale({2270, 1807, 100});
			Stage->GetMap()->SetTexture("Stage1.png");
		}

		{	//��Ż ������
			Stage->GetPortal()->GetTransform().SetLocalScale({ 90, 201, 100 });
			Stage->GetPortal()->SetTexture("Portal.png");

			Stage->GetPortal()->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
			Stage->GetPortal()->ChangeFrameAnimation("Portal");
			Stage->GetPortal()->GetTransform().SetLocalPosition({ 720.0f,-330.0f,0.0f });
		}
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
		GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);//�۽���:����//����:����
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	OnEvent();

	CameraChase();

	NextStage();

	CameraRange();
}

void Stage1Level::End()
{
}

void Stage1Level::CameraChase()
{
	//������ ��������� ���Ͱ���������� Player�� �����θ� ��������0���� �����ص� ���ͳѾ�鼭 �ٽ� ���̹ٲ� �۵��� �ȵȴ�. 
	Camera->GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ NewPlayer->GetTransform().GetLocalPosition() });

}

void Stage1Level::NextStage()
{
	//���� �������� �̵�
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Stage2");
	}
}

void Stage1Level::CameraRange()
{
	//ī�޶� �ʹ����� �ȳ�����
	if (-490 > Camera->GetTransform().GetLocalPosition().x)//���� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = -490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
		//GameEngineDebug::OutPutString(std::to_string(CameraPos.x));//��ǥ ��� �Լ�
	}

	if (490 < Camera->GetTransform().GetLocalPosition().x)//������ �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.x = 490;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (-516 > Camera->GetTransform().GetLocalPosition().y)//y�� �Ʒ� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = -516;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}

	if (100 < Camera->GetTransform().GetLocalPosition().y)//y�� �� ����
	{
		float4 CameraPos = Camera->GetTransform().GetLocalPosition();
		CameraPos.y = 100;
		Camera->GetTransform().SetLocalPosition(CameraPos);
	}
}

void Stage1Level::OnEvent()
{
	if (BgmOn == false)
	{	//������ �ѹ��� ����ǵ��� �ȱ׷��� �����뷡ó�� Ʋ������
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("MapleLeaf.mp3");
		BgmPlayer.Volume(0.05f);
		BgmOn = true;
	}
}
