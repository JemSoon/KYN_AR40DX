#pragma once
#include <GameEngineCore/CoreMinimal.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineTextureRenderer;
class DamageNumber : public GameEngineActor
{
public:
	//디폴트 생성자
	DamageNumber();
	//디폴트 소멸자
	~DamageNumber();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	DamageNumber(const DamageNumber& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	DamageNumber(DamageNumber&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	DamageNumber& operator=(const DamageNumber& _Other) = delete;
	DamageNumber& operator=(DamageNumber&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void DamageRender();
	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetParentMonster(Monster* _Parent)
	{
		Mob = _Parent;
	}

protected:

private:
	GameEngineTextureRenderer* Renderer;
	Monster* Mob;
	int nDamageFont;
};

