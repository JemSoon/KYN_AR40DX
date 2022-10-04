#include "PreCompile.h"
#include "Inventory.h"
#include "GameEngineCore/GameEngineUIRenderer.h"

Inventory* Inventory::Inven = nullptr;
Inventory* Inventory::BeforeInven = nullptr;

Inventory::Inventory() 
	:Money(0)
{
	Inven = this;
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	this->SetLevelOverOn();
	ItemWindow = CreateComponent<GameEngineUIRenderer>();
	ItemWindow->SetTexture("Inven.png");
	ItemWindow->GetTransform().SetWorldScale({175,289,1});
	ItemWindow->GetTransform().SetLocalPosition({ 0, 0,0 });
	//ItemWindow->Off();

	{
		Font = CreateComponent<GameEngineFontRenderer>();
		Font->SetRenderingOrder(1001);
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetParent(this);
		Font->SetPositionMode(FontPositionMode::WORLD);
		Font->SetSize(15.0f);
		//Font->SetText("0");
		Font->SetText(std::to_string(Money));
		Font->SetColor({ 0.0f, 0.0f, 0.0f });
		Font->GetTransform().SetLocalPosition({ 40.0f,-120.0f,0.0f });
		//Font->SetScreenPostion({ 1190.0f, 280.0f ,-350.0f });
		Font->SetLeftAndRightSort(LeftAndRightSort::RIGHT);
	}
	CreateInventory(4, 6, { 32,32 }, 0);

}

void Inventory::LevelEndEvent()
{
	Inven = nullptr;
	BeforeInven = this;
}

void Inventory::Update(float _DeltaTime)
{
	Font->SetText(std::to_string(Money));
}

void Inventory::CreateInventory(int X, int Y, float4 Size, int CollisionOrder)
{
	ItemSlots.resize(Y);

	for (size_t y = 0; y < ItemSlots.size(); y++)
	{
		ItemSlots[y].resize(X);

		for (size_t x = 0; x < ItemSlots[y].size(); x++)
		{
			ItemSlots[y][x] = CreateComponent<ItemIcon>();
			ItemSlots[y][x]->GetTransform().SetLocalScale(Size);
			//���ΰ���4�ȼ� ���ΰ���2�ȼ�
			ItemSlots[y][x]->GetTransform().SetLocalPosition(float4{ -63 + (Size.x * x+(4*x)), -92 + (Size.y * y+(2*y)), -350.0f });
			
		}
	}
}

void Inventory::LevelStartEvent()
{
	if (BeforeInven != nullptr)
	{
		//���� �̵��Ҷ� ������ �÷��̾� ������
		this->Font = BeforeInven->Font;
		this->Money = BeforeInven->Money;
		this->ItemSlots = BeforeInven->ItemSlots;
	}

	Font->ChangeCamera(CAMERAORDER::UICAMERA);
	Inven = this;
	BeforeInven = nullptr;
}