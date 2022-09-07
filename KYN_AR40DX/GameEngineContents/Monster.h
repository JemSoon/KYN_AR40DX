#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
// 설명 : 기본 달팽이
class Player;
class DamageNumber;
class Monster : public CharacterObject
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;
	
	bool MonsterHit(GameEngineCollision* _This, GameEngineCollision* _Other);

	int GetDamage()
	{
		return Damage;
	}
	int SetDamage(int _Att)
	{
		Damage = _Att;
		return Damage;
	}
	int GetHP()
	{
		return HP;
	}

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
	Player* PlayerInfo;	

	int Damage;
	float PatternTime;
	int Random;
	int RandomDir;
	int HP;
	bool Hit;
};

