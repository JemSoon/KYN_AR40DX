#pragma once
#include <GameEngineCore/CoreMinimal.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class Stage1 : public GameEngineActor
{
public:
	//디폴트 생성자
	Stage1();
	//디폴트 소멸자
	~Stage1();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Stage1(const Stage1& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Stage1(Stage1&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Stage1& operator=(const Stage1& _Other) = delete;
	Stage1& operator=(Stage1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) {}
	void End() {}

	GameEngineTextureRenderer* BG;
	GameEngineTextureRenderer* Map;

private:

};

