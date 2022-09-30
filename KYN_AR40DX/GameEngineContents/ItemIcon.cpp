#include "PreCompile.h"
#include "ItemIcon.h"

ItemIcon::ItemIcon()
{

}

ItemIcon::~ItemIcon()
{

}

void ItemIcon::Start()
{
	GameEngineTextureRenderer::Start();

	Renderer = GetActor()->CreateComponent<GameEngineUIRenderer>();
	Renderer->SetTexture("nTest.png");
	Renderer->SetParent(this);
	//Renderer->GetTransform().SetLocalScale({ 32,32,1 });
	//Renderer->GetTransform().SetLocalPosition({ 0, 0,-200 });

	Collision = GetActor()->CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	Collision->SetDebugCamera(CAMERAORDER::UICAMERA);
	//Collision->GetTransform().SetLocalScale({ 30,30,1 });
	//Collision->GetTransform().SetLocalPosition({ 0, 0,-200 });

}

void ItemIcon::Update(float _Delta)
{
}

