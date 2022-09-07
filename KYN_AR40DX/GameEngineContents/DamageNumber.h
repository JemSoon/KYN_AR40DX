#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class DamageNumber : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageNumber();
	~DamageNumber();

	// delete Function
	DamageNumber(const DamageNumber& _Other) = delete;
	DamageNumber(DamageNumber&& _Other) noexcept = delete;
	DamageNumber& operator=(const DamageNumber& _Other) = delete;
	DamageNumber& operator=(DamageNumber&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	GameEngineTextureRenderer* Number;
};

