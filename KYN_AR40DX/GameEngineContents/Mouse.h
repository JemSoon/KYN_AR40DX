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

	float4 GetCursorPos()
	{
		return CursorPos;
	}

protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* MouseImage;
	GameEngineCameraActor* Camera;
	float4 CursorPos;
};

