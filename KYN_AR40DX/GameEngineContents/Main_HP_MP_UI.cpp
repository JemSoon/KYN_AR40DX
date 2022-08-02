#include "PreCompile.h"
#include "Main_HP_MP_UI.h"


Main_HP_MP_UI::Main_HP_MP_UI()
	:HP_MP(nullptr)
	,EXP(nullptr)
{

}

Main_HP_MP_UI::~Main_HP_MP_UI()
{

}

void Main_HP_MP_UI::Start()
{
	// UI는 기본 텍스쳐 렌더러 위에 올라가니 텍스쳐랜더러 z값(1)보다 위에(작아야)있어야한다
	//-100으로 통일하자
	GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
	GetTransform().SetLocalScale({ 1, 1, 1 });
	//Renderer->ChangeCamera(CAMERAORDER::MAINCAMERA);

	{
		HP_MP = CreateComponent<GameEngineUIRenderer>();
		HP_MP->GetTransform().SetLocalScale({ 204,70,-100 });
		HP_MP->SetTexture("mainHP_MP_UI.png");
	}

	{
		EXP = CreateComponent<GameEngineUIRenderer>();
		EXP->GetTransform().SetLocalScale({ 1280, 10, -100 });
		EXP->GetTransform().SetLocalPosition({0,-35});
		EXP->SetTexture("mainEXP_UI.png");
	}
}

