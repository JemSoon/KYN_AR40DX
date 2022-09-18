#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 보스 달팽이 마노
class Player;
class DamageNumber;
class BossMano : public Monster
{
public:
	//디폴트 생성자
	BossMano();
	//디폴트 소멸자
	~BossMano();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BossMano(const BossMano& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BossMano(BossMano&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BossMano& operator=(const BossMano& _Other) = delete;
	BossMano& operator=(BossMano&& _Other) noexcept = delete;

	bool BossManoHit(GameEngineCollision* _This, GameEngineCollision* _Other);

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

	int Damage;
	float PatternTime;
	int Random;
	int RandomDir;
	bool Hit;
};

