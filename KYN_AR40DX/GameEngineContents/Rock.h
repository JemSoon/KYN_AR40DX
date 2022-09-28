#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 시작할때 튜토리얼 하는 NPC
class Dialogue;
class Rock : public CharacterObject
{
public:
	//디폴트 생성자
	Rock();
	//디폴트 소멸자
	~Rock();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	Rock(const Rock& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Rock(Rock&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Rock& operator=(const Rock& _Other) = delete;
	Rock& operator=(Rock&& _Other) noexcept = delete;

	void ChatOn();
	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	Dialogue* Chat;
	std::string Level;
	Player* PlayerInfo;
private:

};

