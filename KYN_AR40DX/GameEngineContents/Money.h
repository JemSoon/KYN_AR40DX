#pragma once
#include "Item.h"
//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 필드에 드롭되는 메소

class Money : public Item
{
public:
	//디폴트 생성자
	Money();
	//디폴트 소멸자
	~Money();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	Money(const Money& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Money(Money&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Money& operator=(const Money& _Other) = delete;
	Money& operator=(Money&& _Other) noexcept = delete;


protected:

private:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
};

