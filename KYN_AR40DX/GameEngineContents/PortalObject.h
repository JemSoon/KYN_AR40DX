#pragma once
#include <GameEngineCore/CoreMinimal.h>
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ��Ż

class PortalObject : public GameEngineActor
{
public:
	//����Ʈ ������
	PortalObject();
	//����Ʈ �Ҹ���
	~PortalObject();
		
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PortalObject(const PortalObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PortalObject(PortalObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PortalObject& operator=(const PortalObject& _Other) = delete;
	PortalObject& operator=(PortalObject&& _Other) noexcept = delete;


protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime);
	virtual void End() {}

private:
	GameEngineTextureRenderer* Portal;
	GameEngineCollision* Collision;
};

