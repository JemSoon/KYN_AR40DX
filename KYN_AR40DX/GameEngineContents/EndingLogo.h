#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class GameEngineTextureRenderer;
class EndingLogo : public GameEngineActor
{
public:
	//디폴트 생성자
	EndingLogo();
	//디폴트 소멸자
	~EndingLogo();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	EndingLogo(const EndingLogo& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	EndingLogo(EndingLogo&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	EndingLogo& operator=(const EndingLogo& _Other) = delete;
	EndingLogo& operator=(EndingLogo&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;

	float TitleTime;
};

