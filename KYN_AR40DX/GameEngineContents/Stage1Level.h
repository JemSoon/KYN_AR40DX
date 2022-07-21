#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 메이플 동산
class Player;
class Stage1Level : public GameEngineLevel
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineCameraActor* Camera;
	Player* NewPlayer;
};

