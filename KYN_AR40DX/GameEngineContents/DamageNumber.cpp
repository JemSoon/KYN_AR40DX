#include "PreCompile.h"
#include "DamageNumber.h"

DamageNumber::DamageNumber()
{

}

DamageNumber::~DamageNumber()
{

}

void DamageNumber::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetTexture("0.png");
	Renderer->ScaleToTexture();
	Renderer->GetTransform().SetWorldPosition({ 0,0,-100 });
}

void DamageNumber::Update(float _DeltaTime)
{
}

