#pragma once
#include "GameEngineRes.h"

//설명 : Res를 상속받아서 여러 과정들을 다 담고있는 파이프라인

class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingPipeLine :public GameEngineRes<GameEngineRenderingPipeLine>
{
public:
	//디폴트 생성자
	GameEngineRenderingPipeLine();
	//디폴트 소멸자
	~GameEngineRenderingPipeLine();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	void Draw();

protected:
	GameEngineInputLayOut* InputLayOut; //인풋어셈블러 1 세팅
	
	GameEngineVertexBuffer* VertexBuffer; //인풋어셈블러1 세팅

	GameEngineVertexShader* VertexShader; //레스터라이저 세팅

	GameEngineIndexBuffer* IndexBuffer; //인풋어셈블러2 세팅

	GameEngineRasterizer* Rasterizer; //레스터라이저 세팅

	GameEnginePixelShader* PixelShader; //픽셀쉐이더 세팅

	GameEngineDepthStencil* DepthStencil; //아웃풋머저 누가 앞인지 세팅

	GameEngineBlend* Blend; //아웃풋 머저 색상통합 세팅

	//아웃풋 머저 중 랜더타겟 세팅은 이미 해놨다
	//디바이스의 백버퍼를 사용해서 만든 랜더타겟이 매번 세팅되고 있다
	//거기에 그려라

private:
	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);
	
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);

	void SetRasterizer(const std::string& _Nmae);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencilSetting(const std::string& _Name);

};

