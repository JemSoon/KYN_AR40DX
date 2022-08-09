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
	Portal->GetTransform().SetLocalScale({ 90, 201, 1 });
	Portal->SetTexture("Portal.png");

	std::vector<unsigned int> Four = { 0, 1, 2, 3 };
	Portal->CreateFrameAnimationCutTexture("Portal", FrameAnimation_DESC("Portal.png", Four, 0.1f));

	Portal->ChangeFrameAnimation("Portal");
	//Portal->SetPivot(PIVOTMODE::BOT);

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 64.0f, 64.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Portal);
	}
}

void PortalObject::Update(float _DeltaTime)
{
}
