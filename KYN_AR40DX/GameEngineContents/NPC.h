#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"


//���� : npc�θ�ü
class Dialogue;
class NPC : public CharacterObject
{
public:
	//����Ʈ ������
	NPC();
	//����Ʈ �Ҹ���
	~NPC();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	NPC(const NPC& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	NPC(NPC&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	NPC& operator=(const NPC& _Other) = delete;
	NPC& operator=(NPC&& _Other) noexcept = delete;

	virtual void ChatOn();
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

