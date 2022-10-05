#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;
	
	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}
	GameEngineTextureRenderer* GetLogoRenderer()
	{
		return LogoRenderer;
	}

	bool MouseThouch(GameEngineCollision* _This, GameEngineCollision* _Other);

	bool IsLevelMove;
	bool SoundOneShot;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

	float TimeAngle;
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* PlayerRenderer;
	GameEngineTextureRenderer* LogoRenderer;
	GameEngineCollision* PlayerCollision;
	float TitleTime;
};

