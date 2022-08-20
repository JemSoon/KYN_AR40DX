#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngineContents/GlobalContentsValue.h>

Mouse::Mouse()
	:MouseImage(nullptr)
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
	GetTransform().SetLocalScale({ 1, 1, 1 });

	MouseImage = CreateComponent<GameEngineUIRenderer>();
	MouseImage->SetTexture("Cursor.png");
	MouseImage->GetTransform().SetWorldScale({ 24,28,0 });
	MouseImage->GetTransform().SetWorldPosition({ CursorPos.x,CursorPos.y,-100 });

}

void Mouse::Update(float _DeltaTime)
{
	CursorPos= GetLevel()->GetUICamera()->GetMouseWorldPosition();
	MouseImage->GetTransform().SetWorldPosition({ CursorPos.x,CursorPos.y,-100 });
}

