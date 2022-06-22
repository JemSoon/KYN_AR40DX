#pragma once
#include "GameEngineCore.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"

// 설명 : 코어 액터 레벨 다 담아둔 공구함(대부분의 기능을 종합)
//!주의!: 절대로 GameEngineCore의 클래스들은 GEngine을 사용하지 않아야 한다
//!이유!: 이 클래스의 기능들은 철저하게 컨텐츠들에게 공개되는 것
class GEngine
{
public:
	static void ChangeLevel(std::string _Name);

private:
	// constrcuter destructer
	GEngine();
	virtual ~GEngine() = 0;

	// delete Function
	GEngine(const GEngine& _Other) = delete;
	GEngine(GEngine&& _Other) noexcept = delete;
	GEngine& operator=(const GEngine& _Other) = delete;
	GEngine& operator=(GEngine&& _Other) noexcept = delete;

protected:
};

