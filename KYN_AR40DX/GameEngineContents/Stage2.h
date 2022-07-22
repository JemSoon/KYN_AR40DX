#pragma once
#include <GameEngineCore/CoreMinimal.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class Stage2 : public GameEngineActor
{
public:
	//디폴트 생성자
	Stage2();
	//디폴트 소멸자
	~Stage2();


	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Stage2(const Stage2& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Stage2(Stage2&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Stage2& operator=(const Stage2& _Other) = delete;
	Stage2& operator=(Stage2&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetPortal() const
	{
		return Portal;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* BG;
	GameEngineTextureRenderer* Map;
	GameEngineTextureRenderer* Map_Col;
	GameEngineTextureRenderer* Portal;

private:
	float Speed;
};

