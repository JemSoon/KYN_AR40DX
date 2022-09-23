#include "PortalObject.h"
#include "PreCompile.h"

PortalObject::PortalObject()
	:Portal(nullptr)
	,Collision(nullptr)
{

}

PortalObject::~PortalObject()
{

}

void PortalObject::Start()
{
	Portal = CreateComponent<GameEngineTextureRenderer>();
	Portal->GetTransform().SetWorldScale({ 90, 201, 1 });
	Portal->GetTransform().SetLocalPosition({ 0,0,-100 });
	Portal->SetTexture("Portal.png");

	std::vector<unsigned int> Four = { 0, 1, 2, 3 };
	Portal->CreateFrameAnimationCutTexture("Portal", FrameAnimation_DESC("Portal.png", Four, 0.1f));

	Portal->ChangeFrameAnimation("Portal");
	//Portal->SetPivot(PIVOTMODE::BOT);

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
		Collision->GetTransform().SetWorldScale({ 32.0f, 64.0f, -100.0f });
		Collision->GetTransform().SetWorldPosition({ 0.0f, -45.0f, -100.0f });
		Collision->ChangeOrder(OBJECTORDER::Portal);
	}
}

void PortalObject::Update(float _DeltaTime)
{
}
