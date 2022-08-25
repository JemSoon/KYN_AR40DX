#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
// 설명 : 기본 달팽이
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
	
	int GetDamage()
	{
		return Damage;
	}
	int SetDamage(int _Att)
	{
		Damage = _Att;
		return Damage;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);
	int Damage;
};

