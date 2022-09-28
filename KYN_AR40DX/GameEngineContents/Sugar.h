#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "NPC.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �����Ҷ� Ʃ�丮�� �ϴ� NPC
class Dialogue;
class Sugar : public NPC
{
public:
	//����Ʈ ������
	Sugar();
	//����Ʈ �Ҹ���
	~Sugar();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Sugar(const Sugar& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Sugar(Sugar&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Sugar& operator=(const Sugar& _Other) = delete;
	Sugar& operator=(Sugar&& _Other) noexcept = delete;

	void ChatOn() override;
	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	//Dialogue* Chat;
	//std::string Level;
	//Player* PlayerInfo;
private:

};

