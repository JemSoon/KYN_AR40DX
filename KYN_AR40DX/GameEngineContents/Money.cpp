#include "Money.h"
#include "PreCompile.h"
Money::Money()
	:MoneyCost(0)
{
	
}

Money::~Money()
{

}

void Money::Start()
{
	Item::Start();
	Type = ItemType::Money;
	Renderer->SetTexture("Money.png");
	Collision->ChangeOrder(OBJECTORDER::Money);
}

void Money::Update(float _DeltaTime)
{
	Item::Update(_DeltaTime);
}

