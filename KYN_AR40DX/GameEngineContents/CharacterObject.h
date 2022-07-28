#pragma once
#include <GameEngineCore/CoreMinimal.h>

//설명 : 몬스터,플레이어,NPC등등 맵에 올라가는 캐릭터들의 공통 부분 부모 클래스
class GameEngineTextureRenderer;
class CharacterObject : public GameEngineActor
{
public:
	//디폴트 생성자
	CharacterObject();
	//디폴트 소멸자
	~CharacterObject();
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	CharacterObject(const CharacterObject& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	CharacterObject(CharacterObject&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	CharacterObject& operator=(const CharacterObject& _Other) = delete;
	CharacterObject& operator=(CharacterObject&& _Other) noexcept = delete;

	virtual inline GameEngineTextureRenderer* GetRenderer() const
	{
		return Renderer;
	}

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime){}
	virtual void End() {}
	virtual void Gravity();
	virtual bool GroundCheck();

	GameEngineTextureRenderer* Renderer;

	float Speed;
	float AccSpeed;
	float DownSpeed;
	float4 FootColorCheck;
private:
};

