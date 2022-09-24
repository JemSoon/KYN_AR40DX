#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Player.h"

// �ڽ��� ��ó�� ���ִ� ��ġ�� ���
// ������Ʈ���� DeathUpdate���� death �ִϸ��̼��� ����Ǹ� �ڽ��� ��� �������� off
// LiveTime = 5.0f

//���� : ���͵��� ���� �θ� Att�� HP������(�������ΰ� �ִ°�)
class Player;
class DamageNumber;
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

	int GetCurHP()
	{
		return MonsterCurHP;
	}
	int GetMaxHP()
	{
		return MonsterHPMax;
	}
	bool IsBuff;
	bool MonsterHit;


protected:
	int MonsterAtt;
	int MonsterCurHP;
	int MonsterHPMax;

	GameEngineTextureRenderer* HPRenderer;
	GameEngineTextureRenderer* HPbarRenderer;

	void Start() override;


	//void Update(float _DeltaTime) 
	//{
	//	if (hp�� 0�̶��)
	//	{
	//		LiveTime -= ��ŸŸ��
	//		if (0.0 >= LiveTime)
	//		{
	//			�������� �ٽ� �� �Ѱ�
	//			GetTransform()->worldpostition(StartPostion);
	//			Renderer->ChangeAnimation(idle);
	//		}
	//		return;
	//	}
	//	// �Ϲ����� �ڵ�
	//}


	void Update(float _DeltaTime);
	void End() {}

	void MonsterHPSetting();
	Player* PlayerInfo;
	DamageNumber* DamageRender;
private:

};

