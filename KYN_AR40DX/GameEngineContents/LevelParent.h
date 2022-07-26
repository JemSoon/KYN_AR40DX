#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "StageObject.h"

// Ό³Έν :
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

	inline void SetMapOnOffSwitch() const
	{
		return LevelStageObject->GetMap()->OnOffSwitch();
	}

	inline GameEngineTextureRenderer* GetMap_Col() const
	{
		return LevelStageObject->GetMap_Col();
	}

	inline GameEngineTextureRenderer* GetPortal() const
	{
		return LevelStageObject->GetPortal();
	}

protected:

	void CreateStageObject(const std::string _MapName, const std::string _ColName);

private:
	StageObject* LevelStageObject;

};

