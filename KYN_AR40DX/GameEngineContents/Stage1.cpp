#include "Stage1.h"

Stage1::Stage1()
	: BG(nullptr)
	, Map(nullptr)
{

}

Stage1::~Stage1()
{

}

void Stage1::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{	//얘를 카메라이동 반응을 1초정도 느리게 쫓아오게 하고 싶다..
		BG = CreateComponent<GameEngineTextureRenderer>();
		BG->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		BG->SetTexture("Stage1_BG.png");
	}

	{
		Map = CreateComponent<GameEngineTextureRenderer>();
		Map->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map->SetTexture("Stage1.png");
	}
}

