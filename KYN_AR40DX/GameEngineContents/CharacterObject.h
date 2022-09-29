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
	DDOWNL,
	DDOWNR,
	CENTER,
	MAX,
};

//���� : ����,�÷��̾�,NPC��� �ʿ� �ö󰡴� ĳ���͵��� ���� �κ� �θ� Ŭ����
class GameEngineTextureRenderer;
class CharacterObject : public GameEngineActor
{
public:
	static const PixelColor WHITE;
	static const PixelColor BLUE;
	static const PixelColor RED;

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

	inline GameEngineCollision* GetCollision() const
	{
		return Collision;
	}

protected:
	virtual void Start() override;
	virtual void End() {}
	virtual void Gravity(float _DeltaTime);

	virtual void NoGravity();

	void ColorCheckUpdate();

	void ColorCheckUpdateNext(float4 MoveColor);


	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;

	float GravitySpeed;
	float Speed;//�̼�
	float4 MovePower;//���ӵ�
	float4 PurePower;//�����ϰ��������� �Ŀ�

	float4 ColorDir[11];

	PixelColor NextColorCheck[11];
	PixelColor ColorCheck[11];
	
	PixelColor PrevColor;
	PixelColor CurColor;

	bool IsNextColor(COLORCHECKDIR _Dir, PixelColor _Color);
	bool IsColor(COLORCHECKDIR _Dir, PixelColor _Color);

private:
};

