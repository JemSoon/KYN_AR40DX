#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

// 설명 : 메이플 동산
class Player;
class Main_HP_MP_UI;
class StageObject;
class Stage1Level : public LevelParent
{
public:
	// constrcuter destructer
	Stage1Level();
	~Stage1Level();

	// delete Function
	Stage1Level(const Stage1Level& _Other) = delete;
	Stage1Level(Stage1Level&& _Other) noexcept = delete;
	Stage1Level& operator=(const Stage1Level& _Other) = delete;
	Stage1Level& operator=(Stage1Level&& _Other) noexcept = delete;

	void CameraRange();
	void NextStage();
	void CameraChase();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void OnEvent() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;
	Main_HP_MP_UI* MainUI;
	GameEngineSoundPlayer BgmPlayer;
	bool BgmOn;
	
};

