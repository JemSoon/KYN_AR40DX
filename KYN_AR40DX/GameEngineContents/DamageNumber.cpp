#include "DamageNumber.h"

DamageNumber::DamageNumber() 
{
}

DamageNumber::~DamageNumber() 
{
}

void DamageNumber::Start()
{
	Number = CreateComponent<GameEngineTextureRenderer>();
	Number->GetTransform().SetLocalScale({ 37, 38, 1 });
	Number->GetTransform().SetLocalPosition({ 0,64,-100 });
	Number->SetTexture("0.png");
}

void DamageNumber::Update(float _DeltaTime)
{
}

