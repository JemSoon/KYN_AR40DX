#pragma once
#include "Player.h"
#include "Monster.h"
#include <GameEngineContents/GlobalContentsValue.h>

enum class OBJECTORDER
{
	Map,
	Player,
	PlayerAtt,
	Monster,
	MonsterSearch,
	NPC,
	Item,
	Portal,
	UI = 1000,
	Mouse,
	Black,
};

//enum class COLLISIONORDER
//{
//	Player,
//	Monster,
//	UI = 1000,
//};

// Ό³Έν :
class GlobalContentsValue
{
public:
	class Enums
	{
	};

	class Actors
	{
	public:
		static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue() {	}

	~GlobalContentsValue() {	}
};

