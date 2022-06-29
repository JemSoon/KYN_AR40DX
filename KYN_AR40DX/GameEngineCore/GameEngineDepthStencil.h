#pragma once
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
public:
	//����Ʈ ������
	GameEngineDepthStencil();
	//����Ʈ �Ҹ���
	~GameEngineDepthStencil();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;


protected:

private:

};

