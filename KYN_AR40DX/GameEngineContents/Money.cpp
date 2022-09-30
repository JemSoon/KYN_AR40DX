#include "Money.h"

Money::Money()
{

}

Money::~Money()
{

}

void Money::Start()
{
	Item::Start();
	Renderer->SetTexture("Money.png");
}

void Money::Update(float _DeltaTime)
{
	Item::Update(_DeltaTime);
}

