#pragma once
#include "CharacterObject.h"
#include <GameEngineCore/CoreMinimal.h>

struct ItemInfo
{
	//�κ��丮�� �������־���� �Űܾ���
	int Count;
	int ID;
};

enum class ItemType
{
	Potion,
	Skill,
};

//���� : 
class Potion : public CharacterObject
{
public:
	//����Ʈ ������
	Potion();
	//����Ʈ �Ҹ���
	~Potion();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Potion(const Potion& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Potion(Potion&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Potion& operator=(const Potion& _Other) = delete;
	Potion& operator=(Potion&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void POPStart(const StateInfo& _Info);
	void POPUpdate(float _DeltaTime, const StateInfo& _Info);

	void DoomChitStart(const StateInfo& _Info);
	void DoomChitUpdate(float _DeltaTime, const StateInfo& _Info);
private:
	float Time;
	GameEngineStateManager StateManager;
};

