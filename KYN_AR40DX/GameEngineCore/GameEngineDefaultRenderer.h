#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineRenderingPipeLine;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
	//랜더링 파이프라인 하나당
	//하나의 메쉬, 하나의 마테리얼, 하나의 랜더타겟 셋트

public:
	GameEngineShaderResourcesHelper ShaderResources;

	//디폴트 생성자
	GameEngineDefaultRenderer();
	//디폴트 소멸자
	~GameEngineDefaultRenderer();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	virtual void Render(float _DeltaTime);//GameEngineRenderer는 순수가상함수로 두고 실질적인 내용물은 디폴트랜더러(여기)

	void SetPipeLine(const std::string& _Name);

	GameEngineRenderingPipeLine* GetPipeLine();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	//네모난 빨간색을 출력한다 등등..
	// 공통적인 메모리 공유하는 메로리들을 들고 있고
	GameEngineRenderingPipeLine* PipeLine;
};

