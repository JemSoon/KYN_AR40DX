#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ItemIcon.h"

// 설명 : 아이템 창
struct ItemInfo
{
	int ItemID;
	int Count;
};
class GameEngineUIRenderer;
class Player;
class GameEngineFontRenderer;
class Inventory :public GameEngineActor
{
public:
	static Inventory* Inven;
	static Inventory* BeforeInven;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	GameEngineFontRenderer* GetFont()
	{
		return Font;
	}
public:
	static Inventory* GetInven()
	{
		return Inven;
	}

	//셋레벨오버온 or 정보옮기기


	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;
	
	void CreateInventory(int X, int Y, float4 Size, int CollisionOrder);
	unsigned int Money;
	std::vector<std::vector<ItemIcon*>> ItemSlots;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* ItemWindow;


private:
	//GameEngineCameraActor* Camera;
	//GameEngineCollision* UICollision;
	Player* PlayerInfo;

	//첫인자에 렌더러
	//std::vector<std::vector<ItemIcon*>> ItemSlots;

	GameEngineFontRenderer* Font;
};

