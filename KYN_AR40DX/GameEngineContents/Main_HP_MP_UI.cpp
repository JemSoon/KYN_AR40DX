#include "Main_HP_MP_UI.h"
#include <GameEngineCore/GameEngineCameraActor.h>

Main_HP_MP_UI::Main_HP_MP_UI()
	:HP_MP(nullptr)
{

}

Main_HP_MP_UI::~Main_HP_MP_UI()
{

}

void Main_HP_MP_UI::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		HP_MP = CreateComponent<GameEngineTextureRenderer>();
		HP_MP->GetTransform().SetLocalScale({ 204,70,1 });
		HP_MP->SetTexture("mainHP_MP_UI.png");
	}

	{
		EXP = CreateComponent<GameEngineTextureRenderer>();
		EXP->GetTransform().SetLocalScale({ 1280, 10, 1 });
		EXP->GetTransform().SetLocalPosition({0,-35});
		EXP->SetTexture("mainEXP_UI.png");
	}
}

