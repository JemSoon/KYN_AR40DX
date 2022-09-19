#pragma once
#include <GameEngineCore/GameEngineActor.h>

//설명 : 보스 체력 ui용 클래스
class GameEngineUIRenderer;
class BossHPUI : public GameEngineActor
{
public:
	//디폴트 생성자
	BossHPUI();
	//디폴트 소멸자
	~BossHPUI();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BossHPUI(const BossHPUI& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BossHPUI(BossHPUI&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BossHPUI& operator=(const BossHPUI& _Other) = delete;
	BossHPUI& operator=(BossHPUI&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineUIRenderer* HPbar;
	GameEngineUIRenderer* HPback;
private:
	int HPbarMaxSize;
	int HPbackMaxSize;
};

