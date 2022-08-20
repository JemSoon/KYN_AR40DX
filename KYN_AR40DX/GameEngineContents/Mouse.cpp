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

	ActorCollision = CreateComponent<GameEngineCollision>();
	ActorCollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 1.0f,0.0f,0.0f,0.3f });
	ActorCollision->GetTransform().SetWorldScale({ 32.0f, 32.0f, 100.0f });
	ActorCollision->ChangeOrder(OBJECTORDER::Mouse);	

	//���� UI�� ������̹����� �����ȵǼ� �Ⱥ������� �浹�ν� Ȯ����
	UICollision = CreateComponent<GameEngineCollision>();
	UICollision->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,0.0f,1.0f,0.3f });
	UICollision->GetTransform().SetWorldScale({ 32.0f, 32.0f, 100.0f });
	UICollision->ChangeOrder(OBJECTORDER::Mouse);
}

void Mouse::Update(float _DeltaTime)
{
	CursorPos1 = GetLevel()->GetMainCamera()->GetMouseWorldPositionToActor();//����ī�޶��
	CursorPos2= GetLevel()->GetUICamera()->GetMouseWorldPosition();//UIī�޶��

	MouseImage->GetTransform().SetWorldPosition({ CursorPos2.x+5,CursorPos2.y-10,-100 });

	ActorCollision->GetTransform().SetWorldPosition({ CursorPos1.x + 5,CursorPos1.y - 10, -200 });
	UICollision->GetTransform().SetWorldPosition({ CursorPos2.x + 645,CursorPos2.y - 403, -200 });

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
	//Ŭ���ϸ� ����Ʈ ��ȭâ�� ���.
	int a = 0;

	return true;
}

bool Mouse::UITestHit(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//���߿� ������ Ŭ���ؼ� ���콺 �����ǿ� �ͼӽ�Ų�� UI�� Ŭ���ϸ� �ű⿡ �Űִܳ´�.
	int a = 0;

	return true;
}