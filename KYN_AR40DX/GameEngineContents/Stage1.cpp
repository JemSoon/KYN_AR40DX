#include "Stage1.h"

Stage1::Stage1()
{

}

Stage1::~Stage1()
{

}

void Stage1::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		BG = CreateComponent<GameEngineTextureRenderer>();
		BG->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		BG->SetTexture("Stage1_BG.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다
	}

	{
		Map = CreateComponent<GameEngineTextureRenderer>();
		Map->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map->SetTexture("Stage1.png");
		//Renderer->ScaleToTexture();//나는 쓰면 늘어난다
	}
}

