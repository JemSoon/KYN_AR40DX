#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngineContents/GlobalContentsValue.h>
#include "Sugar.h"
#include "Dialogue.h"

Mouse::Mouse()
	:MouseImage(nullptr)
{

}

Mouse::~Mouse()
{

}

void Mouse::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Click"))
	{
		GameEngineInput::GetInst()->CreateKey("Click", VK_LBUTTON);
	}

	GameEngineUIRenderer* Renderer = CreateComponent<GameEngineUIRenderer>();
	GetTransform().SetLocalScale({ 1, 1, 1 });

	MouseImage = CreateComponent<GameEngineUIRenderer>();
	//MouseImage = CreateComponent<GameEngineTextureRenderer>();
	MouseImage->SetTexture("Cursor.png");
	MouseImage->GetTransform().SetWorldScale({ 24,28,0 });
	MouseImage->GetTransform().SetWorldPosition({ CursorPos2.x,CursorPos2.y,-100 });
	MouseImage->SetRenderingOrder(1002);

	ActorCollision = CreateComponent<GameEngineCollision>();
	ActorCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	ActorCollision->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });
	ActorCollision->ChangeOrder(OBJECTORDER::Mouse);	

	//현재 UI는 디버그이미지가 구현안되서 안보이지만 충돌인식 확인함
	UICollision = CreateComponent<GameEngineCollision>();
	UICollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	UICollision->GetTransform().SetWorldScale({ 4.0f, 4.0f, 100.0f });
	UICollision->ChangeOrder(OBJECTORDER::Mouse);
	UICollision->SetUIDebugCamera();
}

void Mouse::Update(float _DeltaTime)
{
	CursorPos1 = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();//메인카메라용
	CursorPos2= GetLevel()->GetUICamera()->GetMouseWorldPositionToActor();//UI카메라용

	MouseImage->GetTransform().SetWorldPosition({ CursorPos2.x+5,CursorPos2.y-10,-300 });

	ActorCollision->GetTransform().SetWorldPosition({ CursorPos1.x - 5,CursorPos1.y + 2, -200 });
	UICollision->GetTransform().SetWorldPosition({ CursorPos2.x - 5,CursorPos2.y + 2, -200 });

	{
		ActorCollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::NPC, CollisionType::CT_OBB2D,
			std::bind(&Mouse::MouseHit, this, std::placeholders::_1, std::placeholders::_2));
	}
	{
		UICollision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::UI, CollisionType::CT_OBB2D,
			std::bind(&Mouse::UITestHit, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Mouse::MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//클릭하면 퀘스트 대화창이 뜬다.
	if (true == GameEngineInput::GetInst()->IsDown("Click"))
	{
		_Other->GetActor<NPC>()->ChatOn();
	}

	return true;
}

bool Mouse::UITestHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//나중에 물약을 클릭해서 마우스 포지션에 귀속시킨후 UI에 클릭하면 거기에 옮겨넣는다.
	int a = 0;

	return true;
}