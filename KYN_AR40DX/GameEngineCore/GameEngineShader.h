#pragma once
#include <string>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <functional>

enum class ShaderType
{
	Vertex,
	Pixel,
	MAX,
};

class GameEngineShader;
class ShaderResSetter : public GameEngineNameObject
{
public:
	GameEngineShader* ParentShader;
	ShaderType ShaderType;
	int BindPoint;
	std::function<void()> SettingFunction;
	std::function<void()> ResetFunction;

public:
	ShaderResSetter()
		: ShaderType(ShaderType::MAX)
		, BindPoint(-1)
		, ParentShader(nullptr)
	{

	}
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
	friend GameEngineShader;
public:
	GameEngineConstantBuffer* Res;
	// 각자가 가진 정보에 대한 주소
	const void* SetData;
	UINT Size;

	// 자기메모리로 할당할 것이다.
	std::vector<char> OriginalData;

	void Setting() const;

public:
	GameEngineConstantBufferSetter()
		: Res(nullptr)
		, SetData(nullptr)
		, Size(-1)
	{

	}
};

class GameEngineTexture;
class GameEngineTextureSetter : public ShaderResSetter
{
	friend GameEngineShader;

public:
	void Setting() const;
	void Reset() const;

public:
	GameEngineTexture* Res;
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{
public:
	void Setting() const;

public:
	GameEngineSampler* Res;
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter : public ShaderResSetter
{
public:
	void Setting() const;

public:
	GameEngineStructuredBuffer* Res;
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
	virtual ~GameEngineShader();

	
	
	
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

	ShaderType ShaderSettingType;

private:
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::map<std::string, GameEngineTextureSetter> TextureMap;
	std::map<std::string, GameEngineSamplerSetter> SamplerMap;
	std::map<std::string, GameEngineStructuredBufferSetter> StructuredBufferMap;

	std::string EntryPoint;

	//std::map<unsigned int, ConstantBuffer>
	// void SetConstantBuffer() override;
};

