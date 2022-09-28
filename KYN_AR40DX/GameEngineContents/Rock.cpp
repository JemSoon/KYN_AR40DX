#include "PreCompile.h"
#include "Rock.h"
#include "Dialogue.h"

Rock::Rock()
{

}

Rock::~Rock()
{

}

void Rock::Start()
{
	NPC::Start();
	//{
	//	Chat = GetLevel()->CreateActor<Dialogue>();
	//	//Level = GetLevel()->GetNameCopy();
	//	Chat->GetTransform().SetWorldPosition({ 0.0f,0.0f,-200.0f });
	//	Chat->Off();
	//}
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 81, 88, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("Rock.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//���� ���� �þ��

		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 70.0f,70.0f,100.0f });
		Collision->ChangeOrder(OBJECTORDER::NPC);
		Collision->GetTransform().SetWorldPosition({ 0,35.0f });
	}
}

void Rock::Update(float _DeltaTime)
{
	//ColorCheckUpdate();

	//if (PlayerInfo == nullptr)
	//{
	//	PlayerInfo = Player::GetMainPlayer();
	//}

	//if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	//{
	//	//���ǹ� �����ָ� ��� �߷¹޾Ƽ� �������� �ε�ε� ��
	//	Gravity(_DeltaTime);
	//}

	//MovePower.x = static_cast<int>(MovePower.x);
	//MovePower.y = static_cast<int>(MovePower.y);

	//GetTransform().SetWorldMove(MovePower * _DeltaTime);

	//NoGravity();
	NPC::Update(_DeltaTime);

	if (Chat->IsUpdate() == true)
	{
		Level = GetLevel()->GetNameCopy();
		GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
		Font->SetRenderingOrder(1001);
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetParent(Chat);
		Font->SetSize(15.0f);
		if (PlayerInfo->PlayerLevel < 10)
		{
			Font->SetText("���簡 �ǰ������ \n�� �� ������ �ϰ� ���ʽÿ�", "����");
		}
		else if (Chat->IsYes == true)
		{
			Font->SetText("�丮�¿� �� �Գ�", "����");
			return;
		}
		else if (Chat->IsYes == false && PlayerInfo->PlayerLevel >= 10)
		{
			Font->SetText("����� �����ϰڽ��ϱ�?", "����");
			Chat->YesOn();
		}
		Font->SetColor({ 0.0f, 0.0f, 0.0f });
		Font->SetScreenPostion({ 540.0f, 270.0f ,-350.0f });
	}

	if (Chat->IsYes == true)
	{
		PlayerInfo->MyJob = JOB::WARRIOR;
		PlayerInfo->IsJobChange = true;
		Chat->IsYes = false;
	}
}

void Rock::ChatOn()
{
	Chat->On();
	Chat->SetNPCTexture("Rock.png");
}