#include "PreCompile.h"
#include "Sugar.h"
#include "Dialogue.h"

Sugar::Sugar()
{

}

Sugar::~Sugar()
{

}

void Sugar::Start()
{
	CharacterObject::Start();
	{
		Chat = GetLevel()->CreateActor<Dialogue>();
		//std::string Level = GetLevel()->GetNameCopy();
		Chat->GetTransform().SetWorldPosition({ 0.0f,0.0f,-200.0f });
		Chat->Off();
	}
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 48, 75, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("sugar.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//���� ���� �þ��

		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetLocalScale({ 40.0f,64.0f,100.0f });
		Collision->ChangeOrder(OBJECTORDER::NPC);
		Collision->GetTransform().SetWorldPosition({0,35.0f});
	}
}

void Sugar::Update(float _DeltaTime)
{
	ColorCheckUpdate();

	if (true == IsColor(COLORCHECKDIR::DOWN, CharacterObject::WHITE))
	{	
		//���ǹ� �����ָ� ��� �߷¹޾Ƽ� �������� �ε�ε� ��
		Gravity(_DeltaTime);
	}

	MovePower.x = static_cast<int>(MovePower.x);
	MovePower.y = static_cast<int>(MovePower.y);

	GetTransform().SetWorldMove(MovePower * _DeltaTime);

	NoGravity();

	if (Chat->IsUpdate() == true)
	{
		GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
		Font->SetRenderingOrder(1001);
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetParent(Chat);
		Font->SetText("�ȳ�", "����");
		Font->SetColor({0.0f, 0.0f, 0.0f });
		Font->SetScreenPostion({ 540.0f, 270.0f ,-350.0f});
	}
}

void Sugar::ChatOn()
{
	Chat->On();
	Chat->SetNPCTexture("sugar.png");
}