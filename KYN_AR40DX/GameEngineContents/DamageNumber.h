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

	void NumberSetting(int _Damage);
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	GameEngineTextureRenderer* NumOne;
	GameEngineTextureRenderer* NumTen;
	GameEngineTextureRenderer* NumHun;
	int nDamageOne;
	int nDamageTen;
	int nDamageHun;

	float Time;
};

