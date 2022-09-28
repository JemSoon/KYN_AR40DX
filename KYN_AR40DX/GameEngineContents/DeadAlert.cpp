#include "PreCompile.h"
#include <GameEngineContents/GlobalContentsValue.h>
#include "DeadAlert.h"

DeadAlert::DeadAlert()
	:IsRespawn(false)
{

}

DeadAlert::~DeadAlert()
{

}

void DeadAlert::Start()
{
	Dialogue = CreateComponent<GameEngineUIRenderer>();
	Dialogue->SetTexture("DeadAlert.png");
	Dialogue->GetTransform().SetWorldScale({ 300,130,1 });
	Dialogue->GetTransform().SetLocalPosition({ 0, 0,-200 });
	Dialogue->SetPivot(PIVOTMODE::CENTER);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	Collision->GetTransform().SetWorldScale({ 40,18,1 });
	Collision->GetTransform().SetLocalPosition({ 115, -45,-250 });
	Collision->ChangeOrder(OBJECTORDER::UI);
	Collision->SetUIDebugCamera();
}

void DeadAlert::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Mouse, CollisionType::CT_OBB2D,
		std::bind(&DeadAlert::MouseHit, this, std::placeholders::_1, std::placeholders::_2));
}

bool DeadAlert::MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("Click"))
	{
		_This->GetActor()->Off();
		IsRespawn = true;
		return true;
	}
}