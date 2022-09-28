#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 페리온 전직하는 곳
class Perion : public LevelParent
{
public:
	//디폴트 생성자
	Perion();
	//디폴트 소멸자
	~Perion();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Perion(const Perion& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Perion(Perion&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Perion& operator=(const Perion& _Other) = delete;
	Perion& operator=(Perion&& _Other) noexcept = delete;

	void CameraRange();

	void CameraChase(float _Delta);

	void LevelMove();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;
	GameEngineSoundPlayer BgmPlayer;
	GameEngineCollision* Collision;
	bool BgmOn;
	float ShipTime;
};

