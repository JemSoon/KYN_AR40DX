#pragma once
#include "CharacterObject.h"
#include <GameEngineCore/CoreMinimal.h>

enum class ItemType
{
	Item,
	Money,
};

//���� : �ʵ忡 �������� ����
class Player;
class Item : public CharacterObject
{
public:
	//����Ʈ ������
	Item();
	//����Ʈ �Ҹ���
	~Item();

	ItemType GetItemType()
	{
		return Type;
	}
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Item(const Item& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Item(Item&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	//bool PlayerEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void POPStart(const StateInfo& _Info);
	void POPUpdate(float _DeltaTime, const StateInfo& _Info);

	void DoomChitStart(const StateInfo& _Info);
	void DoomChitUpdate(float _DeltaTime, const StateInfo& _Info);

	bool PlayerEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	ItemType Type;
	Player* PlayerInfo;
private:
	float Time;
	GameEngineStateManager StateManager;
};

