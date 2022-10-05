#pragma once
#include "CharacterObject.h"
#include <GameEngineCore/CoreMinimal.h>

enum class ItemType
{
	Item,
	Money,
};

//설명 : 필드에 떨어지는 포션
class Player;
class Item : public CharacterObject
{
public:
	//디폴트 생성자
	Item();
	//디폴트 소멸자
	~Item();

	ItemType GetItemType()
	{
		return Type;
	}
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Item(const Item& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Item(Item&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
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

