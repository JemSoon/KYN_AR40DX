#pragma once
#include <string>
#include <map>

class ConstantBuffer
{

};

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineShader
{
public:
	static void AutoCompile(const std::string& _Path);

	//����Ʈ ������
	GameEngineShader();
	//����Ʈ �Ҹ���
	~GameEngineShader();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineShader(const GameEngineShader& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;


protected:
	void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);
	void SetEntryPoint(const std::string& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	ID3DBlob* BinaryPtr;

	std::string Version;

	void ShaderResCheck();

private:
	std::string EntryPoint;

	std::map<unsigned int, ConstantBuffer>

};

