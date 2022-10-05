#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "LevelParent.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 달팽이 언덕
class Player;
class StageObject;
class BossMano;
class Snail;
class Stage2Level : public LevelParent
{
public:
	//디폴트 생성자
	Stage2Level();
	//디폴트 소멸자
	~Stage2Level();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Stage2Level(const Stage2Level& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Stage2Level(Stage2Level&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Stage2Level& operator=(const Stage2Level& _Other) = delete;
	Stage2Level& operator=(Stage2Level&& _Other) noexcept = delete;

	void CameraChase(float _Delta);
	void NextStage();
	void CameraRange();
	void LevelMove();
	void MonsterRespawnPosition(Monster* _Mob, float4 _Position);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelStartEvent() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;

	BossMano* Mano;
	Snail* Snail1;
	Snail* Snail2;
};

