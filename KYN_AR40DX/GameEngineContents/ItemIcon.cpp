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
	//GameEngineTextureRenderer::Start();
	//GameEngineTextureRenderer::ChangeCamera(CAMERAORDER::UICAMERA);
	
	Renderer = GetActor()->CreateComponent<GameEngineUIRenderer>();
	Renderer->SetTexture("nTest.png");
	Renderer->SetParent(this);
	Renderer->GetTransform().SetLocalPosition({ 0,0,-2 });
	Renderer->ChangeCamera(CAMERAORDER::UICAMERA);
	
	//Font = GetActor()->CreateComponent<GameEngineFontRenderer>();
	//Font->SetText("0");
	//Font->SetParent(this);
	//Font->SetScreenPostion(Renderer->GetTransform().GetLocalPosition());
	//Font->SetSize(15.0f);
	//Font->SetColor({ 0.0f, 0.0f, 0.0f });

	Collision = GetActor()->CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	Collision->SetDebugCamera(CAMERAORDER::UICAMERA);
	//Collision->SetUIDebugCamera();
	//Collision->GetTransform().SetLocalScale({ 30,30,1 });
	//Collision->GetTransform().SetLocalPosition({ 0, 0,-200 });
}

void ItemIcon::Update(float _Delta)
{
	if (Renderer->GetCurTexture()->GetNameCopy() == "NTEST.PNG")
	{
		Renderer->Off();
	}
	else
	{
		Renderer->On();
	}
}

