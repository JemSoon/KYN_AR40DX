#pragma once
#include <GameEngineCore/CoreMinimal.h>

//���� : ����,�÷��̾�,NPC��� �ʿ� �ö󰡴� ĳ���͵��� ���� �κ� �θ� Ŭ����
class GameEngineTextureRenderer;
class CharacterObject : public GameEngineActor
{
public:
	//����Ʈ ������
	CharacterObject();
	//����Ʈ �Ҹ���
	~CharacterObject();
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	CharacterObject(const CharacterObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	CharacterObject(CharacterObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	CharacterObject& operator=(const CharacterObject& _Other) = delete;
	CharacterObject& operator=(CharacterObject&& _Other) noexcept = delete;

	virtual inline GameEngineTextureRenderer* GetRenderer() const
	{
		return Renderer;
	}

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime){}
	virtual void End() {}
	virtual void Gravity();
	virtual bool GroundCheck();

	GameEngineTextureRenderer* Renderer;

	float Speed;
	float AccSpeed;
	float DownSpeed;
	float4 FootColorCheck;
private:
};

