#pragma once
#include <GameEngineCore/CoreMinimal.h>

//���� : ���ӳ� ���콺
class GameEngineTextureRenderer;
class Mouse : public GameEngineActor
{
public:
	//����Ʈ ������
	Mouse();
	//����Ʈ �Ҹ���
	~Mouse();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Mouse(const Mouse& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Mouse(Mouse&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetMouse()
	{
		return MouseImage;
	}

	float4 GetCursorPos1()
	{
		return CursorPos1;
	}

	float4 GetCursorPos2()
	{
		return CursorPos2;
	}

	GameEngineCollision* GetMouseActorCol()
	{
		return ActorCollision;
	}

	GameEngineCollision* GetMouseUICol()
	{
		return UICollision;
	}

	bool MouseHit(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool UITestHit(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* MouseImage;
	GameEngineCameraActor* Camera;
	float4 CursorPos1;
	float4 CursorPos2;
	GameEngineCollision* ActorCollision;
	GameEngineCollision* UICollision;

};

