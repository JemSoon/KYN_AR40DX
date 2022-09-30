#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"
// 설명 : 기본 달팽이
class Player;
class DamageNumber;
class Item;
class Money;
class Snail : public Monster
{
public:
	// constrcuter destructer
	Snail();
	~Snail();

	// delete Function
	Snail(const Snail& _Other) = delete;
	Snail(Snail&& _Other) noexcept = delete;
	Snail& operator=(const Snail& _Other) = delete;
	Snail& operator=(Snail&& _Other) noexcept = delete;
	
	bool SnailHit(GameEngineCollision* _This, GameEngineCollision* _Other);

	void MonsterRespawn();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void HitStart(const StateInfo& _Info);
	void HitUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeadStart(const StateInfo& _Info);
	void DeadUpdate(float _DeltaTime, const StateInfo& _Info);

	void ChaseStart(const StateInfo& _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo& _Info);

	void DieEnd();

private:
	GameEngineStateManager StateManager;
	DamageNumber* Num;
	Item* WPotion;
	Money* Coin;

	int Damage;
	float PatternTime;
	int Random;
	int RandomDir;
	int RandomDrop;

	//bool Hit;
};

