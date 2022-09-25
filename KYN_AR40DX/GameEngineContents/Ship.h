#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 메이플 아일랜드에서 빅토리아로 가는 배 맵
class Player;
class StageObject;
class Ship : public LevelParent
{
public:
	//디폴트 생성자
	Ship();
	//디폴트 소멸자
	~Ship();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======	
	//디폴트 복사 생성자
	Ship(const Ship& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Ship(Ship&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Ship& operator=(const Ship& _Other) = delete;
	Ship& operator=(Ship&& _Other) noexcept = delete;
	//====================================================

	void CameraRange();
	//void NextStage();
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
	bool BgmOn;
	float ShipTime;
};

