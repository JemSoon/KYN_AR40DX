#include "PreCompile.h"
#include "Sugar.h"

Sugar::Sugar()
{

}

Sugar::~Sugar()
{

}

void Sugar::Start()
{
	//��ӿ� ���
	//GetTransform().SetLocalScale({ 1, 1, 1 });
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 48, 75, 1 });
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->SetTexture("sugar.png");
		Renderer->SetPivot(PIVOTMODE::BOT);
		//Renderer->ScaleToTexture();//���� ���� �þ��

	}
}

void Sugar::Update(float _DeltaTime)
{
	if (_DeltaTime >= 0.1f)
	{
		_DeltaTime = 0.0f;
	}

	Gravity(_DeltaTime);
}

