#pragma once
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineBlend : public GameEngineRes<GameEngineBlend>
{
public:
	//����Ʈ ������
	GameEngineBlend();
	//����Ʈ �Ҹ���
	~GameEngineBlend();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(GameEngineBlend&& _Other) noexcept = delete;


protected:

private:

};

