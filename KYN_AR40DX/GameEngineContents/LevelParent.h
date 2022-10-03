#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "StageObject.h"
#include "PortalObject.h"
#include "Black.h"

// Ό³Έν :
class Main_HP_MP_UI;
class Mouse;
class Black;
class Inventory;
class LevelParent : public GameEngineLevel
{
public:
	// constrcuter destructer
	LevelParent();
	~LevelParent();

	// delete Function
	LevelParent(const LevelParent& _Other) = delete;
	LevelParent(LevelParent&& _Other) noexcept = delete;
	LevelParent& operator=(const LevelParent& _Other) = delete;
	LevelParent& operator=(LevelParent&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetBG() const
	{
		return LevelStageObject->GetBG();
	}

	inline GameEngineTextureRenderer* GetMap() const
	{
		return LevelStageObject->GetMap();
	}

	//inline void SetMapOnOffSwitch() const
	//{
	//	if (GameEngineInput::GetInst()->IsDown("MapOffSwitch"))
	//	{
	//		return LevelStageObject->GetMap()->OnOffSwitch(), LevelStageObject->GetBG()->OnOffSwitch();
	//	}
	//}

	inline GameEngineTextureRenderer* GetMap_Col() const
	{
 		return LevelStageObject->GetMap_Col();
	}

	void BlackTimeOut();
protected:
	void CreateStageObject(const std::string _BG, const std::string _ColName, const std::string _MapName);

	StageObject* LevelStageObject;
	PortalObject* Portal;
	Main_HP_MP_UI* MainUI;
	Mouse* Cursor;
	Black* B;
	GameEngineSoundPlayer BgmPlayer;
	bool BgmOn;
	float BlackOutTime;
	float BlackInTime;

	bool LevelIn;
private:
};

