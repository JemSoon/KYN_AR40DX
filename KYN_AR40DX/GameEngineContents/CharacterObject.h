#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class COLORCHECKDIR
{
	LEFT,
	LEFTTOP,
	RIGHT,
	RIGHTTOP,
	UP,
	DOWN,
	DOWNL,
	DOWNR,
	MAX,
};

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
	virtual void End() {}
	virtual void Gravity(float _DeltaTime);

	void ColorCheckUpdate();

	void ColorCheckUpdateNext(float4 MoveColor);


	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;

	float Speed;//�̼�
	float GravityAccSpeed;
	float4 MovePower;//���ӵ�

	float4 ColorDir[8];

	float4 ColorCheck[8];
	float4 NextColorCheck[8];

	bool IsNextColor(COLORCHECKDIR _Dir, float4 _Color);

private:
};

