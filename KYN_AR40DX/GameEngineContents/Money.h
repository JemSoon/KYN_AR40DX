#pragma once
#include "Item.h"
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �ʵ忡 ��ӵǴ� �޼�

class Money : public Item
{
public:
	//����Ʈ ������
	Money();
	//����Ʈ �Ҹ���
	~Money();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Money(const Money& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Money(Money&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Money& operator=(const Money& _Other) = delete;
	Money& operator=(Money&& _Other) noexcept = delete;


protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
};

