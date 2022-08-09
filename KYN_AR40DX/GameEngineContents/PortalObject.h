#pragma once
#include <GameEngineCore/CoreMinimal.h>
//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 포탈

class PortalObject : public GameEngineActor
{
public:
	//디폴트 생성자
	PortalObject();
	//디폴트 소멸자
	~PortalObject();
		
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	PortalObject(const PortalObject& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	PortalObject(PortalObject&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	PortalObject& operator=(const PortalObject& _Other) = delete;
	PortalObject& operator=(PortalObject&& _Other) noexcept = delete;


protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime);
	virtual void End() {}

private:
	GameEngineTextureRenderer* Portal;
	GameEngineCollision* Collision;
};

