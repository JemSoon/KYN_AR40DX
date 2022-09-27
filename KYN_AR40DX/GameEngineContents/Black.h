#pragma once
#include <GameEngineCore/CoreMinimal.h>
//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class Black : public GameEngineActor
{
public:
	//디폴트 생성자
	Black();
	//디폴트 소멸자
	~Black();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Black(const Black& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Black(Black&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Black& operator=(const Black& _Other) = delete;
	Black& operator=(Black&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}
	
protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime);
	virtual void End() {}

private:
	GameEngineUIRenderer* Renderer;
};

