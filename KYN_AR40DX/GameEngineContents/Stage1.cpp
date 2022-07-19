#include "Stage1.h"

Stage1::Stage1()
	: BG(nullptr)
	, Map(nullptr)
	, Portal(nullptr)
	, Map_Col(nullptr)
{

}

Stage1::~Stage1()
{

}

void Stage1::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{	//�÷��浹 ��
		Map_Col = CreateComponent<GameEngineTextureRenderer>();
		Map_Col->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map_Col->SetTexture("Stage1_Col.png");

		//�޹��	�긦 ī�޶��̵� ������ 1������ ������ �Ѿƿ��� �ϰ� �ʹ�..
		BG = CreateComponent<GameEngineTextureRenderer>();
		BG->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		BG->SetTexture("Stage1_BG.png");
	}

	{	//��¥ �׸� ��
		Map = CreateComponent<GameEngineTextureRenderer>();
		Map->GetTransform().SetLocalScale({ 2270, 1807, 100 });
		Map->SetTexture("Stage1.png");
	}

	{	//��Ż ������
		Portal = CreateComponent<GameEngineTextureRenderer>();
		Portal->GetTransform().SetLocalScale({ 90, 201, 100 });
		Portal->SetTexture("Portal.png");

		Portal->CreateFrameAnimation("Portal", FrameAnimation_DESC("Portal.png", 0, 3, 0.1f));
		Portal->ChangeFrameAnimation("Portal");
	}
}

