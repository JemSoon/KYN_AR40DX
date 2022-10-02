#pragma once
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class ItemIcon : public GameEngineUIRenderer
{
public:
	//디폴트 생성자
	ItemIcon();
	//디폴트 소멸자
	~ItemIcon();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	ItemIcon(const ItemIcon& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	ItemIcon(ItemIcon&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	ItemIcon& operator=(const ItemIcon& _Other) = delete;
	ItemIcon& operator=(ItemIcon&& _Other) noexcept = delete;

	GameEngineUIRenderer* GetRenderer()
	{
		return Renderer;
	}

	GameEngineCollision* GetCollision()
	{
		return Collision;
	}

	void Start() override;

	void Update(float _Delta) override;

public:
	GameEngineUIRenderer* Renderer;

	GameEngineCollision* Collision;

};

