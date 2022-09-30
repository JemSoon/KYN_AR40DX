#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : ������ â
struct ItemInfo
{
	int ItemID;
	int Count;
};
class GameEngineUIRenderer;
class Player;
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

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* ItemWindow;

private:
	GameEngineCameraActor* Camera;
	GameEngineCollision* UICollision;
	Player* PlayerInfo;

	//ù���ڿ� ������
	std::vector<std::pair<GameEngineUIRenderer, ItemInfo>> ItemList;

	GameEngineFontRenderer* Font;
};

