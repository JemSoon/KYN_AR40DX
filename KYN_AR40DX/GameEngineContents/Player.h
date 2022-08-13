#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"

// ���� :
class GameEngineRandom;
class GameEngineCollision;
class GameEngineTextureRenderer;
class Player : public CharacterObject
{
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

	bool stop;//BG�����̱��
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	bool MonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	float4 GetMovePower()
	{
		return MovePower;
	}
	
	bool PortalOn;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	//==========================================================//
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	//void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void SadariStart(const StateInfo& _Info);
	void SadariUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void FallStart(const StateInfo& _Info);
	void FallUpdate(float _DeltaTime, const StateInfo& _Info);

	void ProneStart(const StateInfo& _Info);
	void ProneUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);

	void DownJumpStart(const StateInfo& _Info);
	void DownJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	//==========================================================//
	void Gravity(float _DeltaTime) override;
	//==========================================================//
	void AttackEnd();
	//==========================================================//
private:
	GameEngineStateManager StateManager;
	float4 Dir;
	GameEngineCollision* AttackCollision;
};

