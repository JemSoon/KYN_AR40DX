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
	UICollision = CreateComponent<GameEngineCollision>();

	{
		Font = CreateComponent<GameEngineFontRenderer>();
		Font->SetRenderingOrder(1001);
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetParent(this);
		Font->SetSize(15.0f);
		Font->SetText("0000000000");
		Font->SetColor({ 0.0f, 0.0f, 0.0f });
		Font->SetScreenPostion({ 1190.0f, 280.0f ,-350.0f });
		Font->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
	}
}

void Inventory::Update(float _DeltaTime)
{

}