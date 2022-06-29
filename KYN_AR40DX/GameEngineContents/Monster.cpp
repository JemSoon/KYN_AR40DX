#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	{
		GameEngineRenderer* RendererTest = CreateComponent<GameEngineDefaultRenderer>();
		//RendererTest->GetTransform().SetLocalScale({ 50, 50, 50 });
	}
}
