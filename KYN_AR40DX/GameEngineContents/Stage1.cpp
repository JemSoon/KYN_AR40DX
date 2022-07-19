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

	{	//�긦 ī�޶��̵� ������ 1������ ������ �Ѿƿ��� �ϰ� �ʹ�..
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

