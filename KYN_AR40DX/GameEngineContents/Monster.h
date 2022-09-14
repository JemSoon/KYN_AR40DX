#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Player.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���͵��� ���� �θ� Att�� HP������(�������ΰ� �ִ°�)
class Player;
class Monster : public CharacterObject
{
public:
	//����Ʈ ������
	Monster();
	//����Ʈ �Ҹ���
	~Monster();
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Monster(const Monster& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Monster(Monster&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	int GetAtt()
	{
		return MonsterAtt;
	}

	int GetHP()
	{
		return MonsterCurHP;
	}

protected:
	int MonsterAtt;
	int MonsterCurHP;
	int MonsterHPMax;

	GameEngineTextureRenderer* HPRenderer;
	GameEngineTextureRenderer* HPbarRenderer;

	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void MonsterHPSetting();
	Player* PlayerInfo;
private:

};

