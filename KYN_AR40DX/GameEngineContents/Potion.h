#pragma once
#include "CharacterObject.h"
#include <GameEngineCore/CoreMinimal.h>

enum class ITEM
{
	Count,
	ID
};

//설명 : 
class Potion : public CharacterObject
{
public:
	//디폴트 생성자
	Potion();
	//디폴트 소멸자
	~Potion();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Potion(const Potion& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Potion(Potion&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Potion& operator=(const Potion& _Other) = delete;
	Potion& operator=(Potion&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	void POPStart(const StateInfo& _Info);
	void POPUpdate(float _DeltaTime, const StateInfo& _Info);

	void DoomChitStart(const StateInfo& _Info);
	void DoomChitUpdate(float _DeltaTime, const StateInfo& _Info);
private:
	float Time;
	GameEngineStateManager StateManager;
};

