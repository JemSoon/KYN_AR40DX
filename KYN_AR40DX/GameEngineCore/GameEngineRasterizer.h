#pragma once
#include "GameEngineRes.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineRasterizer : public GameEngineRes<GameEngineRasterizer>
{
public:
	static GameEngineRasterizer* Create(const std::string& _Name, const D3D11_RASTERIZER_DESC& _Desc);

public:
	//디폴트 생성자
	GameEngineRasterizer();
	//디폴트 소멸자
	~GameEngineRasterizer();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;


	void Setting();

protected:

private:
	D3D11_RASTERIZER_DESC Desc;
	ID3D11RasterizerState* State;
	// D3D11_RASTERIZER_DESC WireDesc_;

	void Create(const D3D11_RASTERIZER_DESC& _Desc);
};

