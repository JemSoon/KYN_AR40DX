#include "PreCompile.h"
#include "GameEngineRandom.h"
#include <chrono>

//!!주의!! 시드를 지역변수로 하면 고정된 랜덤값이 나온다!! 멤버변수로 사용해 주자!!

GameEngineRandom GameEngineRandom::MainRandom;

GameEngineRandom::GameEngineRandom(long long _Seed /*= -1*/)
// : mt_(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
	if (_Seed != -1)
	{
		mt_ = std::mt19937_64(_Seed);
	}
	else
	{
		mt_ = std::mt19937_64(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	}
}

GameEngineRandom::~GameEngineRandom()
{
}

