#pragma once
#include "GameEngineShader.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineVertexShader
	: public GameEngineRes<GameEngineVertexShader>
	, public GameEngineShader
{
public:
	//디폴트 생성자
	GameEngineVertexShader();
	//디폴트 소멸자
	~GameEngineVertexShader();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

	static GameEngineVertexShader* Load(std::string _Path, std::string _EntryPoint , UINT _VersionHigh = 5, UINT _VersionLow=0);
	static GameEngineVertexShader* Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT VersionLow);

protected:

private:

};

