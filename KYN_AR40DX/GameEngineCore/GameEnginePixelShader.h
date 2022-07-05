#pragma once
#include "GameEngineShader.h"
#include "GameEngineRes.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEnginePixelShader
	: public GameEngineRes<GameEnginePixelShader>
	, public GameEngineShader
{
	friend GameEngineShader;
	friend GameEngineRes<GameEnginePixelShader>;

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


	static GameEnginePixelShader* Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	static GameEnginePixelShader* Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);
	
protected:
	void ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

private:
	ID3D11PixelShader* ShaderPtr;

};

