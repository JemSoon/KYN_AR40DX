#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "LevelParent.h"

// ���� : ������ ����
class Player;
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
	
};

