#pragma once
#include "Monster.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���� ������ ����
class BossMano : public Monster
{
public:
	//����Ʈ ������
	BossMano();
	//����Ʈ �Ҹ���
	~BossMano();
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BossMano(const BossMano& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BossMano(BossMano&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BossMano& operator=(const BossMano& _Other) = delete;
	BossMano& operator=(BossMano&& _Other) noexcept = delete;


protected:

private:

};

