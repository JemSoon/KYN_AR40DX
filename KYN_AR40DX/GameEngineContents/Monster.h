#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Player.h"

// 자신이 맨처음 서있던 위치를 기억
// 업데이트에서 DeathUpdate에서 death 애니메이션이 종료되면 자신의 모든 랜더러를 off
// LiveTime = 5.0f

//설명 : 몬스터들의 상위 부모 Att와 HP설정용(공통적인걸 넣는곳)
class Player;
class DamageNumber;
class Monster : public CharacterObject
{
public:
	//디폴트 생성자
	Monster();
	//디폴트 소멸자
	~Monster();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Monster(const Monster& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Monster(Monster&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
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
	//	if (hp가 0이라면)
	//	{
	//		LiveTime -= 델타타임
	//		if (0.0 >= LiveTime)
	//		{
	//			랜더러를 다시 다 켜고
	//			GetTransform()->worldpostition(StartPostion);
	//			Renderer->ChangeAnimation(idle);
	//		}
	//		return;
	//	}
	//	// 일반적인 코드
	//}


	void Update(float _DeltaTime);
	void End() {}

	void MonsterHPSetting();
	Player* PlayerInfo;
	DamageNumber* DamageRender;
private:

};

