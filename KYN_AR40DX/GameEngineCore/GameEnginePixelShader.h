#pragma once
#include "GameEngineShader.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEnginePixelShader
	: public GameEngineRes<GameEnginePixelShader>
	, public GameEngineShader
{
public:
	//����Ʈ ������
	GameEnginePixelShader();
	//����Ʈ �Ҹ���
	~GameEnginePixelShader();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;


protected:

private:

};

