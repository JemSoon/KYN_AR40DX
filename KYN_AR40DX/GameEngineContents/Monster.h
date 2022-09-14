#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Player.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 몬스터들의 상위 부모 Att와 HP설정용(공통적인걸 넣는곳)
class Player;
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

