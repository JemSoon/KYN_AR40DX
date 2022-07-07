#pragma once
#include "GameEngineDevice.h"
#include "GameEngineRes.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineLayOutDesc;
class GameEngineVertexShader;
class GameEngineInputLayOut : public GameEngineRes<GameEngineInputLayOut>
{
public:
	//디폴트 생성자
	GameEngineInputLayOut();
	//디폴트 소멸자
	~GameEngineInputLayOut();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Create(const GameEngineLayOutDesc& _Desc, GameEngineVertexShader* _Shader);

	void Setting();

protected:

private:
	ID3D11InputLayout* InputLayOut;
};

