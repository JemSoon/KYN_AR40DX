#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���͵��� ���� �θ� Att�� HP������
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
		return MonsterHP;
	}

protected:
	int MonsterAtt;
	int MonsterHP;

private:

};

