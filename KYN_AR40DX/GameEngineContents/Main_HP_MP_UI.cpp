#include "PreCompile.h"
#include "Main_HP_MP_UI.h"


Main_HP_MP_UI::Main_HP_MP_UI()
	:HP_MP(nullptr)
	,EXP(nullptr)
	,HPbarMaxSize(171)
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
		HPbar = CreateComponent<GameEngineUIRenderer>();
		HPbar->SetTexture("HPbar.png");
		HPbar->GetTransform().SetWorldScale({ (float)HPbarMaxSize,13,-100 });
		HPbar->GetTransform().SetWorldPosition({ 10,0,-100 });
		//HPbar->SetPivot(PIVOTMODE::LEFTTOP);

		MPbar = CreateComponent<GameEngineUIRenderer>();
		MPbar->SetTexture("MPbar.png");
		MPbar->GetTransform().SetWorldScale({ 171,13,0 });
		MPbar->GetTransform().SetWorldPosition({ 10,-15,-100 });
	}

	{
		HP_MP = CreateComponent<GameEngineUIRenderer>();
		HP_MP->GetTransform().SetWorldScale({ 204,70,-100 });
		HP_MP->GetTransform().SetWorldPosition({ 0,0,-100 });
		HP_MP->SetTexture("mainHP_MP_UI.png"); 
	}

	{
		EXP = CreateComponent<GameEngineUIRenderer>();
		EXP->GetTransform().SetWorldScale({ 1280, 10, -100 });
		EXP->GetTransform().SetWorldPosition({0,-35,-100});
		EXP->SetTexture("mainEXP_UI.png");
	}

	{
		EXPbar = CreateComponent<GameEngineUIRenderer>();
		EXPbar->GetTransform().SetWorldScale({ 1264, 7, 0 });
		EXPbar->GetTransform().SetWorldPosition({ 7,-35,-100 });
		EXPbar->SetTexture("EXPbar.png");
	}

	{
		QuickSlot = CreateComponent<GameEngineUIRenderer>();
		QuickSlot->GetTransform().SetWorldScale({151, 80, 0});
		QuickSlot->GetTransform().SetWorldPosition({564, 8, -100});
		QuickSlot->SetTexture("QuickSlot.png");

		TESTUICollision= CreateComponent<GameEngineCollision>();
		TESTUICollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
		TESTUICollision->GetTransform().SetWorldScale({ 151, 80, 100.0f });
		TESTUICollision->GetTransform().SetWorldPosition({ 1204, -392, -100 });
		TESTUICollision->ChangeOrder(OBJECTORDER::UI);
	}
}

void Main_HP_MP_UI::Update(float _DeltaTime)
{
	if (PlayerInfo == nullptr)
	{
		PlayerInfo = Player::GetMainPlayer();
	}

	HPbarMaxSize =( 171 * PlayerInfo->CurHP )/ 100;
	HPbar->GetTransform().SetWorldScale({ (float)HPbarMaxSize,13,0 });
	
	if (HPbarMaxSize >= 0)
	{
		HPbarMaxSize = 0;
	}
}

