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
	//MouseImage = CreateComponent<GameEngineTextureRenderer>();
	MouseImage->SetTexture("Cursor.png");
	MouseImage->GetTransform().SetWorldScale({ 24,28,0 });
	MouseImage->GetTransform().SetWorldPosition({ CursorPos2.x,CursorPos2.y,-100 });

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	Collision->GetTransform().SetWorldScale({ 32.0f, 32.0f, 100.0f });
	Collision->ChangeOrder(OBJECTORDER::Mouse);	
}

void Mouse::Update(float _DeltaTime)
{
	CursorPos1 = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();
	CursorPos2= GetLevel()->GetUICamera()->GetMouseWorldPositionToActor();
	MouseImage->GetTransform().SetWorldPosition({ CursorPos2.x+5,CursorPos2.y-10,-100 });
	Collision->GetTransform().SetWorldPosition({ CursorPos1.x + 5,CursorPos1.y - 10, -200 });

	{
		Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::NPC, CollisionType::CT_OBB2D,
			std::bind(&Mouse::MouseHit, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Mouse::MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//클릭하면 퀘스트 대화창이 뜬다.
	int a = 0;

	return true;
}