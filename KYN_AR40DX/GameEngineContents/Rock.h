#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �����Ҷ� Ʃ�丮�� �ϴ� NPC
class Dialogue;
class Rock : public CharacterObject
{
public:
	//����Ʈ ������
	Rock();
	//����Ʈ �Ҹ���
	~Rock();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	Rock(const Rock& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Rock(Rock&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Rock& operator=(const Rock& _Other) = delete;
	Rock& operator=(Rock&& _Other) noexcept = delete;

	void ChatOn();
	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	Dialogue* Chat;
	std::string Level;
	Player* PlayerInfo;
private:

};

