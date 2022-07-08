#pragma once
#include <string>
#include <map>

class ConstantBuffer
{

};

class ShaderResSetter
{
public:
	int BindPoint;
	std::string* Name;
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
public:
	GameEngineConstantBuffer* Buffer;
};

class GameEngineConstantBuffer;
class GameEngineTextureSetter : public ShaderResSetter
{
};

//설명 : 
class GameEngineShaderResourcesHelper;
class GameEngineShader
{
	friend GameEngineShaderResourcesHelper;

public:
	static void AutoCompile(const std::string& _Path);

	//디폴트 생성자
	GameEngineShader();
	//디폴트 소멸자
	~GameEngineShader();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineShader(const GameEngineShader& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineConstantBufferSetter& GetConstantBufferSetter(std::string _Name);

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
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::map<std::string, GameEngineTextureSetter> TextureSetterMap;

	std::string EntryPoint;

	//std::map<unsigned int, ConstantBuffer>

};

