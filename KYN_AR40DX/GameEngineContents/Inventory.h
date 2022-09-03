#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 아이템 창
class GameEngineTextureRenderer;
class Player;
class Inventory :public GameEngineActor
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* ItemWindow;

private:
	GameEngineCameraActor* Camera;
	GameEngineCollision* UICollision;
	Player* PlayerInfo;
};

