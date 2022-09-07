#include "DamageNumber.h"

DamageNumber::DamageNumber() 
	:nDamageFont(0)
{
}

DamageNumber::~DamageNumber() 
{
}

void DamageNumber::Start()
{
	Number = CreateComponent<GameEngineTextureRenderer>();
	Number->GetTransform().SetLocalScale({ 37, 38, 1 });
	Number->GetTransform().SetLocalPosition({ 0,64,-400 });
	Number->SetTexture("0.png");
}

void DamageNumber::Update(float _DeltaTime)
{
}

void DamageNumber::NumberSetting(int _Damage)
{
	while (_Damage > 0)
	{
		nDamageFont = _Damage % 10;
		_Damage = _Damage / 10;
		{
			//두번째 자리수 이동설정
		}
	}

	switch (nDamageFont)
	{
	case 1:
		Number->SetTexture("1.png");
		break;
	case 2:
		Number->SetTexture("2.png");
		break;
	case 3:
		Number->SetTexture("3.png");
		break;
	case 4:
		Number->SetTexture("4.png");
		break;
	case 5:
		Number->SetTexture("5.png");
		break;
	case 6:
		Number->SetTexture("6.png");
		break;
	case 7:
		Number->SetTexture("7.png");
		break;
	case 8:
		Number->SetTexture("8.png");
		break;
	case 9:
		Number->SetTexture("9.png");
		break;
	default:
		Number->SetTexture("0.png");
		break;
	}

}