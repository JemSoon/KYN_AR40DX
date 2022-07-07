#pragma once
#include "GameEngineDevice.h"
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineLayOutDesc;
class GameEngineVertexShader;
class GameEngineInputLayOut : public GameEngineRes<GameEngineInputLayOut>
{
public:
	//����Ʈ ������
	GameEngineInputLayOut();
	//����Ʈ �Ҹ���
	~GameEngineInputLayOut();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Create(const GameEngineLayOutDesc& _Desc, GameEngineVertexShader* _Shader);

	void Setting();

protected:

private:
	ID3D11InputLayout* InputLayOut;
};

