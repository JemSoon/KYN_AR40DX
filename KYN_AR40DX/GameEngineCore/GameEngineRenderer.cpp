#include "GameEngineRenderer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	GetActor()->GetLevel()->PushRenderer(this);
}

void GameEngineRenderer::Render(float _DeltaTime)
{
	Rectangle(GameEngineWindow::GetHDC(), 100, 100, 200, 200);
}