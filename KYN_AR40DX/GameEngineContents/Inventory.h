#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ItemIcon.h"

// ���� : ������ â
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
	static Inventory* GetInst()
	{
		static Inventory Inst;
		return &Inst;
	}

	//�·��������� or �����ű��


	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;
	
	void CreateInventory(int X, int Y, float4 Size, int CollisionOrder);
	int Money;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* ItemWindow;


private:
	//GameEngineCameraActor* Camera;
	//GameEngineCollision* UICollision;
	Player* PlayerInfo;

	//ù���ڿ� ������
	std::vector<std::vector<ItemIcon*>> ItemSlots;

	GameEngineFontRenderer* Font;
};

