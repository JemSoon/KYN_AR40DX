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
}

void Sugar::ChatOn()
{
	
	Chat->On();
	
}