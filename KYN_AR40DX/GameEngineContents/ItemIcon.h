#pragma once
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class ItemIcon : public GameEngineUIRenderer
{
public:
	//����Ʈ ������
	ItemIcon();
	//����Ʈ �Ҹ���
	~ItemIcon();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	ItemIcon(const ItemIcon& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	ItemIcon(ItemIcon&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	ItemIcon& operator=(const ItemIcon& _Other) = delete;
	ItemIcon& operator=(ItemIcon&& _Other) noexcept = delete;

	GameEngineUIRenderer* GetRenderer()
	{
		return Renderer;
	}

	GameEngineCollision* GetCollision()
	{
		return Collision;
	}

	void Start() override;

	void Update(float _Delta) override;

public:
	GameEngineUIRenderer* Renderer;

	GameEngineCollision* Collision;

};

