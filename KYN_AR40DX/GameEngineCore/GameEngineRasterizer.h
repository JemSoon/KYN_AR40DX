#pragma once
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineRasterizer : public GameEngineRes<GameEngineRasterizer>
{
public:
	//����Ʈ ������
	GameEngineRasterizer();
	//����Ʈ �Ҹ���
	~GameEngineRasterizer();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;


protected:

private:

};

