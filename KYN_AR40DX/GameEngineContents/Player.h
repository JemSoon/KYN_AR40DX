#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Player : public CharacterObject
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	bool GroundCheck();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float4 Color;
};

