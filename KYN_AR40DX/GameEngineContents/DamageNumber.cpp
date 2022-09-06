#include "PreCompile.h"
#include "DamageNumber.h"
#include "Monster.h"

DamageNumber::DamageNumber()
	:nDamageFont(0)
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
	DamageRender();
}

void DamageNumber::DamageRender()
{
	int Damage = Mob->nDamage;
	while (Damage > 0)
	{
		nDamageFont = Damage % 10;
		Damage = Damage / 10;
		switch (nDamageFont)
		{
		case 1:
			Renderer->SetTexture("1.png");
			break;

		case 2:
			Renderer->SetTexture("2.png");
			break;

		case 3:
			Renderer->SetTexture("3.png");
			break;

		case 4:
			Renderer->SetTexture("4.png");
			break;

		case 5:
			Renderer->SetTexture("5.png");
			break;

		case 6:
			Renderer->SetTexture("6.png");
			break;

		case 7:
			Renderer->SetTexture("7.png");
			break;

		case 8:
			Renderer->SetTexture("8.png");
			break;

		case 9:
			Renderer->SetTexture("9.png");
			break;

		default:
			Renderer->SetTexture("0.png");
			break;
		}
	}
}