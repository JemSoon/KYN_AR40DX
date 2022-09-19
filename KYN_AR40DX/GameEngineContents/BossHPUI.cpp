#include "PreCompile.h"
#include "BossHPUI.h"


BossHPUI::BossHPUI()
	:HPbar(nullptr)
	,HPback(nullptr)
{

}

BossHPUI::~BossHPUI()
{

}

void BossHPUI::Start()
{
	HPback = CreateComponent<GameEngineUIRenderer>();
	HPback->SetTexture("boss_hp_bg.png");
	HPback->GetTransform().SetWorldScale({ 801,37,1 });
	HPback->GetTransform().SetLocalPosition({ 0, 0,-100 });
	HPback->SetPivot(PIVOTMODE::LEFT);

	HPbar = CreateComponent<GameEngineUIRenderer>();
	HPbar->SetTexture("boss_hp_bar.png");
	HPbar->GetTransform().SetWorldScale({ 758,12,1 });
	HPbar->GetTransform().SetLocalPosition({ 39, -1,-100 });
	HPbar->SetPivot(PIVOTMODE::LEFT);
}

void BossHPUI::Update(float _DeltaTime)
{

}

