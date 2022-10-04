#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"
#include "Monster.h"

enum class JOB
{
	NONE,
	WARRIOR,
	MAGITION,
	THIEF,
	ARCHER,
	MAX
};

// 설명 :

class GameEngineRandom;
class GameEngineCollision;
class GameEngineTextureRenderer;
class DeadAlert;
class Inventory;
class Player : public CharacterObject
{
private:
	static Player* MainPlayer;
	static Player* BeforePlayer;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

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
	bool MonsterSlashBlastHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool MonsterUpperChargeHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool MonsterLeafAttackHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PlayerHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool MoneyEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool PotionEatCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	GameEngineCollision* GetAttCollision()
	{
		return AttackCollision;
	}

	GameEngineCollision* GetSlashBlastCollision()
	{
		return SlashBlastCollision;
	}

	GameEngineCollision* GetUpperChargeCollision()
	{
		return UpperChargeCollision;
	}

	GameEngineCollision* GetLeafAttackCollision()
	{
		return LeafAttackCollision;
	}

	float4 GetMovePower()
	{
		return MovePower;
	}
	
	int GetFinalAtt()
	{
		return FinalAtt;
	}

	void SetPlayerAttBuff(float _Value)
	{
		FinalAtt = PlayerAtt * _Value;;
	}

	float GetDirX()
	{
		return Dir.x;
	}

	bool PortalOn;
	bool HitCheck;
	bool IsSkill;
	int HitDamage;
	int ManaDamage;
	int HPMax;
	int CurHP;
	int MPMax;
	int CurMP;
	int EXPMax;
	int CurEXP;
	int PlayerLevel;
	//bool OneAtt;
	bool IsLevelUp;
	bool IsJobChange;
	float GroundMoveSpeed;
	float JumpMoveSpeed;
	float JumpPower;
	float SuperJumpPower;

	int MonsterCount;
	int ItemCount;

	JOB MyJob;

	void Dead();
	void LevelUp();
	void UpToGround();
	void AlertColor();

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

	void SuperJumpStart(const StateInfo& _Info);
	void SuperJumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void FallStart(const StateInfo& _Info);
	void FallUpdate(float _DeltaTime, const StateInfo& _Info);

	void ProneStart(const StateInfo& _Info);
	void ProneUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);

	void DownJumpStart(const StateInfo& _Info);
	void DownJumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void SlashBlast1Start(const StateInfo& _Info);
	void SlashBlast1Update(float _DeltaTime, const StateInfo& _Info);
				   
	void SlashBlast2Start(const StateInfo& _Info);
	void SlashBlast2Update(float _DeltaTime, const StateInfo& _Info);

	void UpperChargeStart(const StateInfo& _Info);
	void UpperChargeUpdate(float _DeltaTime, const StateInfo& _Info);

	void LeafAttackStart(const StateInfo& _Info);
	void LeafAttackUpdate(float _DeltaTime, const StateInfo& _Info);

	//==========================================================//
	//==========================================================//
	void AttackEnd();
	void LevelUpEnd();
	void SuperJumpEnd();
	void SlashBlast1End();
	void SlashBlast2End();
	void UpperChargeEnd();
	void LeafAttackEnd();
	//==========================================================//
	void PlayerRespawn();

private:
	GameEngineStateManager StateManager;
	float4 Dir;
	GameEngineCollision* AttackCollision;
	GameEngineCollision* SlashBlastCollision;
	GameEngineCollision* UpperChargeCollision;
	GameEngineCollision* LeafAttackCollision;
	std::string PrevState;
	bool Hit;
	float HitTime;
	int PlayerAtt;
	int FinalAtt;
	GameEngineTextureRenderer* PlayerLevelUp;
	GameEngineTextureRenderer* Effect;
	GameEngineTextureRenderer* SlashBlast1;
	GameEngineTextureRenderer* SlashBlast2;
	GameEngineTextureRenderer* UpperCharge;
	GameEngineTextureRenderer* LeafAttack;
	GameEngineTextureRenderer* RIP;

	int UseSuperJump;
	int UseSlashBlast;
	int UseUpperCharge;

	GameEngineActor* GhostActor;
	DeadAlert* DieMessage;

	float4 DeadPosition;

	//Inventory* Inven;
};

//class 잔상 : public GameEngineActor
//{
//	std::vector<GameEngineTextureRenderer*> AllPartsRenderer;
//
//public:
//	void Start() 
//	{
//		Death(0.2f);
//
//		// 
//		//HPRenderer->renderOption.Option00 = 1;
//	}
//
//	텍스처세팅(Player* _Player) 
//	{
//		for (size_t i = 0; i < _Player->AllPartsRenderer.size(); i++)
//		{
//			AllPartsRenderer[i]->SetTexture(_Player->AllPartsRenderer[i]->GetCurTexture());
//		}
//	}
//
//	업데이트() 
//	{
//		for (size_t i = 0; i < _Player->AllPartsRenderer.size(); i++)
//		{
//			AllPartsRenderer[i]->GetPixelData().PlusColor.a -= 델타타임;
//		}
//
//		// 점점 
//	}
//};