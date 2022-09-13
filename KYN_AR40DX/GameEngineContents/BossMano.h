#pragma once
#include "Monster.h"

//�������� ������ �͵鵵 ���������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���� ������ ����
class BossMano : public Monster
{
public:
	//����Ʈ ������
	BossMano();
	//����Ʈ �Ҹ���
	~BossMano();
	
	//======�Ʒ��͵��� ���������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BossMano(const BossMano& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BossMano(BossMano&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BossMano& operator=(const BossMano& _Other) = delete;
	BossMano& operator=(BossMano&& _Other) noexcept = delete;

	//bool BossManoHit(GameEngineCollision* _This, GameEngineCollision* _Other);

	//int GetDamage()
	//{
	//	return Damage;
	//}
	//int SetDamage(int _Att)
	//{
	//	Damage = _Att;
	//	return Damage;
	//}
	//int GetHP()
	//{
	//	return HP;
	//}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	/*void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void HitStart(const StateInfo& _Info);
	void HitUpdate(float _DeltaTime, const StateInfo& _Info);

	void DeadStart(const StateInfo& _Info);
	void DeadUpdate(float _DeltaTime, const StateInfo& _Info);

	void ChaseStart(const StateInfo& _Info);
	void ChaseUpdate(float _DeltaTime, const StateInfo& _Info);

	void DieEnd();*/

private:
	/*GameEngineStateManager StateManager;
	DamageNumber* Num;
	Player* PlayerInfo;

	int Damage;
	float PatternTime;
	int Random;
	int RandomDir;
	int HP;
	bool Hit;*/
};
