#include "PreCompile.h"
#include "Inventory.h"

Inventory::Inventory() 
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	ItemWindow = CreateComponent<GameEngineUIRenderer>();
	ItemWindow->SetTexture("Inven.png");
	ItemWindow->GetTransform().SetWorldScale({175,289,-100});
	ItemWindow->GetTransform().SetLocalPosition({ 0, 0,-100 });
	ItemWindow->Off();
	UICollision = CreateComponent<GameEngineCollision>();
}

void Inventory::Update(float _DeltaTime)
{

}