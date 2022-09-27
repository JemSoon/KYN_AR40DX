#include "PreCompile.h"
#include <GameEngineContents/GlobalContentsValue.h>
#include "Dialogue.h"

Dialogue::Dialogue()
{

}

Dialogue::~Dialogue()
{

}

void Dialogue::Start()
{
	Chat = CreateComponent<GameEngineUIRenderer>();
	Chat->SetTexture("UtilDlg.png");
	Chat->GetTransform().SetWorldScale({ 529,246,1 });
	Chat->GetTransform().SetLocalPosition({ 0, 0,-200 });
	Chat->SetPivot(PIVOTMODE::CENTER);

	Exit = CreateComponent<GameEngineUIRenderer>();
	Exit->SetTexture("UtilDlgExit.png");
	Exit->GetTransform().SetWorldScale({ 85,18,1 });
	Exit->GetTransform().SetLocalPosition({ 210, -105,-250 });
	Exit->SetPivot(PIVOTMODE::CENTER);

	NPC = CreateComponent<GameEngineUIRenderer>();
	NPC->SetTexture("sugar.png");
	NPC->GetTransform().SetWorldScale({ -48,75,1 });
	NPC->GetTransform().SetLocalPosition({ -180, 0,-250 });
	NPC->SetPivot(PIVOTMODE::CENTER);

	ExitCollision = CreateComponent<GameEngineCollision>();
	ExitCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	ExitCollision->GetTransform().SetWorldScale({ 85,18,1 });
	ExitCollision->GetTransform().SetLocalPosition({ 210, -105,-250 });
	ExitCollision->ChangeOrder(OBJECTORDER::UI);
	ExitCollision->SetUIDebugCamera();
}

void Dialogue::Update(float _DeltaTime)
{
	ExitCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Mouse, CollisionType::CT_OBB2D,
		std::bind(&Dialogue::MouseHit, this, std::placeholders::_1, std::placeholders::_2));

}

void Dialogue::SetNPCTexture(const std::string _Name)
{
	NPC->SetTexture(_Name);
}

bool Dialogue::MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("Click"))
	{
		_This->GetActor()->Off();
	}

	return true;
}