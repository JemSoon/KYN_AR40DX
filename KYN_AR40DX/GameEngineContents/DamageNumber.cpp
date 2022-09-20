#include "DamageNumber.h"

DamageNumber::DamageNumber()
	: nDamageOne(0)
	, nDamageTen(0)
	, nDamageHun(0)
	, Time(0.0f)
{
}

DamageNumber::~DamageNumber() 
{
}

void DamageNumber::Start()
{
	NumOne = CreateComponent<GameEngineTextureRenderer>();
	NumOne->GetTransform().SetLocalScale({ 37, 38, 1 });
	NumOne->GetTransform().SetLocalPosition({ 25,64,-400 });
	NumOne->SetTexture("0.png");

	NumTen = CreateComponent<GameEngineTextureRenderer>();
	NumTen->GetTransform().SetLocalScale({ 37, 38, 1 });
	NumTen->GetTransform().SetLocalPosition({ 0,59,-400 });
	NumTen->SetTexture("0.png");

	NumHun = CreateComponent<GameEngineTextureRenderer>();
	NumHun->GetTransform().SetLocalScale({ 37, 38, 1 });
	NumHun->GetTransform().SetLocalPosition({ -25,64,-400 });
	NumHun->SetTexture("0.png");
	NumHun->Off();
}

void DamageNumber::Update(float _DeltaTime)
{
	Time += (GameEngineTime::GetDeltaTime()*10.0f);

	NumOne->GetTransform().SetLocalPosition({ 25, 64 + Time,-400 });
	NumTen->GetTransform().SetLocalPosition({ 0, 59 + Time,-400 });
	NumHun->GetTransform().SetLocalPosition({ -25, 64 + Time,-400 });

	NumOne->GetPixelData().MulColor.a -= _DeltaTime;
	NumTen->GetPixelData().MulColor.a -= _DeltaTime;
	NumHun->GetPixelData().MulColor.a -= _DeltaTime;

	if (Time >= 10.0f)
	{
		this->Death();
	}
}

void DamageNumber::NumberSetting(int _Damage)
{
	while (_Damage > 0)
	{
		nDamageOne = _Damage % 10;
		_Damage = _Damage / 10;
		nDamageTen = _Damage % 10;
		_Damage = _Damage / 10;
		nDamageHun = _Damage % 10;
		_Damage = _Damage / 10;
	}

	switch (nDamageOne)
	{
	case 1:
		NumOne->SetTexture("1.png");
		NumOne->ScaleToTexture();
		break;
	case 2:
		NumOne->SetTexture("2.png");
		NumOne->ScaleToTexture();
		break;
	case 3:
		NumOne->SetTexture("3.png");
		NumOne->ScaleToTexture();
		break;
	case 4:
		NumOne->SetTexture("4.png");
		NumOne->ScaleToTexture();
		break;
	case 5:
		NumOne->SetTexture("5.png");
		NumOne->ScaleToTexture();
		break;
	case 6:
		NumOne->SetTexture("6.png");
		NumOne->ScaleToTexture();
		break;
	case 7:
		NumOne->SetTexture("7.png");
		NumOne->ScaleToTexture();
		break;
	case 8:
		NumOne->SetTexture("8.png");
		NumOne->ScaleToTexture();
		break;
	case 9:
		NumOne->SetTexture("9.png");
		NumOne->ScaleToTexture();
		break;
	default:
		NumOne->SetTexture("0.png");
		NumOne->ScaleToTexture();
		break;
	}

	switch (nDamageTen)
	{
	case 1:
		NumTen->SetTexture("1.png");
		NumTen->ScaleToTexture();
		break;
	case 2:
		NumTen->SetTexture("2.png");
		NumTen->ScaleToTexture();
		break;
	case 3:
		NumTen->SetTexture("3.png");
		NumTen->ScaleToTexture();
		break;
	case 4:
		NumTen->SetTexture("4.png");
		NumTen->ScaleToTexture();
		break;
	case 5:
		NumTen->SetTexture("5.png");
		NumTen->ScaleToTexture();
		break;
	case 6:
		NumTen->SetTexture("6.png");
		NumTen->ScaleToTexture();
		break;
	case 7:
		NumTen->SetTexture("7.png");
		NumTen->ScaleToTexture();
		break;
	case 8:
		NumTen->SetTexture("8.png");
		NumTen->ScaleToTexture();
		break;
	case 9:
		NumTen->SetTexture("9.png");
		NumTen->ScaleToTexture();
		break;
	case 0:
		NumTen->SetTexture("0.png");
		NumTen->ScaleToTexture();
		if (nDamageHun == 0)
		{
			NumTen->Off();
		}
		break;
	default:
		NumTen->SetTexture("0.png");
		NumTen->ScaleToTexture();
		break;
	}

	switch (nDamageHun)
	{
	case 1:
		NumHun->SetTexture("1.png");
		NumHun->ScaleToTexture();
		break;
	case 2:
		NumHun->SetTexture("2.png");
		NumHun->ScaleToTexture();
		break;
	case 3:
		NumHun->SetTexture("3.png");
		NumHun->ScaleToTexture();
		break;
	case 4:
		NumHun->SetTexture("4.png");
		NumHun->ScaleToTexture();
		break;
	case 5:
		NumHun->SetTexture("5.png");
		NumHun->ScaleToTexture();
		break;
	case 6:
		NumHun->SetTexture("6.png");
		NumHun->ScaleToTexture();
		break;
	case 7:
		NumHun->SetTexture("7.png");
		NumHun->ScaleToTexture();
		break;
	case 8:
		NumHun->SetTexture("8.png");
		NumHun->ScaleToTexture();
		break;
	case 9:
		NumHun->SetTexture("9.png");
		NumHun->ScaleToTexture();
		break;
	case 0:
		NumHun->SetTexture("0.png");
		NumHun->ScaleToTexture();
		NumHun->Off();
		break;
	default:
		NumHun->SetTexture("0.png");
		NumHun->ScaleToTexture();
		break;
	}
}