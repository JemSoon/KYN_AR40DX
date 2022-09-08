#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Monster.h"

// 설명 :

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

	bool stop;//BG움직이기용
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	bool MonsterHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PlayerHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	float4 GetMovePower()
	{
		return MovePower;
	}
	
	int GetPlayerAtt()
	{
		return PlayerAtt;
	}

	float GetDirX()
	{
		return Dir.x;
	}

	bool PortalOn;
	bool HitCheck;
	int HitDamage;
	int HPMax;
	int CurHP;
	int EXPMax;
	int CurEXP;
	int PlayerLevel;
	bool OneAtt;
	bool IsLevelUp;
	float GroundMoveSpeed;
	float JumpMoveSpeed;
	float JumpPower;

	void Dead();
	void LevelUp();
	void UpToGround();
	void NoGravity();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	//==========================================================//
	void DeadStart(const StateInfo& _Info);
	void DeadUpdate(float _DeltaTime, const StateInfo& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
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

	void AlertStart(const StateInfo& _Info);
	void AlertUpdate(float _DeltaTime, const StateInfo& _Info);
	//==========================================================//
	//==========================================================//
	void AttackEnd();
	void LevelUpEnd();
	//==========================================================//
	void AlertToIdle();

private:
	GameEngineStateManager StateManager;
	float4 Dir;
	GameEngineCollision* AttackCollision;
	std::string PrevState;
	bool Hit;
	float HitTime;
	Monster Mob;
	int PlayerAtt;
	GameEngineTextureRenderer* PlayerLevelUp;
};

