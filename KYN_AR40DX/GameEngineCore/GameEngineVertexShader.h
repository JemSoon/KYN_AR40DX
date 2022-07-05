#pragma once
#include "GameEngineShader.h"
#include "GameEngineRes.h"

//���� : 
class GameEngineInputLayOut;
class GameEngineVertexShader
	: public GameEngineRes<GameEngineVertexShader>
	, public GameEngineShader
{
	friend GameEngineInputLayOut;
	friend GameEngineShader;
	friend GameEngineRes<GameEngineVertexShader>;

private:
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
	void ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

private:
	ID3D11VertexShader* ShaderPtr;

};

