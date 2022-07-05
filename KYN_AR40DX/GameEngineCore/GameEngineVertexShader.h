#pragma once
#include "GameEngineShader.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineVertexShader
	: public GameEngineRes<GameEngineVertexShader>
	, public GameEngineShader
{
public:
	//����Ʈ ������
	GameEngineVertexShader();
	//����Ʈ �Ҹ���
	~GameEngineVertexShader();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

	static GameEngineVertexShader* Load(std::string _Path, std::string _EntryPoint , UINT _VersionHigh = 5, UINT _VersionLow=0);
	static GameEngineVertexShader* Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT VersionLow);

protected:

private:

};

