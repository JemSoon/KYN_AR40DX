#pragma once
#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Map,
	Player,
	PlayerAtt,
	Monster,
	NPC,
	Portal,
	UI = 1000,
	Mouse,
};

//enum class COLLISIONORDER
//{
//	Player,
//	Monster,
//	UI = 1000,
//};

// ���� :
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

