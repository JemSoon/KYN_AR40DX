#pragma once
#include <GameEngineCore/CoreMinimal.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 퀘스트 대화창
class GameEngineUIRenderer;
class Dialogue : public GameEngineActor
{
public:
	//디폴트 생성자
	Dialogue();
	//디폴트 소멸자
	~Dialogue();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Dialogue(const Dialogue& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Dialogue(Dialogue&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Dialogue& operator=(const Dialogue& _Other) = delete;
	Dialogue& operator=(Dialogue&& _Other) noexcept = delete;

	bool MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other);
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* Chat;
	GameEngineUIRenderer* Exit;
	GameEngineCollision* ExitCollision;
private:

};

