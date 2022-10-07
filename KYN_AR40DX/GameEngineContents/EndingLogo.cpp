#include "PreCompile.h"
#include "EndingLogo.h"

EndingLogo::EndingLogo()
{

}

EndingLogo::~EndingLogo()
{

}

void EndingLogo::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 1 });
		Renderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 800.0f });
		Renderer->SetTexture("Ending.png");
	}

	{
		std::vector<unsigned int> Two = { 0, 1 };
		Renderer->CreateFrameAnimationCutTexture("Ending", FrameAnimation_DESC("Ending.png", Two, 0.3f));
		
		Renderer->ChangeFrameAnimation("Ending");
	}
}

void EndingLogo::Update(float _DeltaTime)
{
}

void EndingLogo::End()
{
}
