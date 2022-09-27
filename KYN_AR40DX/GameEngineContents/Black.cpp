#include "Black.h"
#include "PreCompile.h"

Black::Black()
{

}

Black::~Black()
{

}

void Black::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->GetTransform().SetWorldScale({ 3000, 3000, 1 });
	Renderer->GetTransform().SetWorldPosition({ 0,0,0 });
	Renderer->SetTexture("Black.png");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Black::Update(float _DeltaTime)
{
}

