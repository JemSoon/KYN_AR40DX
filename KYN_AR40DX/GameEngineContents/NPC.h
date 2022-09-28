#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "CharacterObject.h"


//설명 : npc부모개체
class Dialogue;
class NPC : public CharacterObject
{
public:
	//디폴트 생성자
	NPC();
	//디폴트 소멸자
	~NPC();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	NPC(const NPC& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	NPC(NPC&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	NPC& operator=(const NPC& _Other) = delete;
	NPC& operator=(NPC&& _Other) noexcept = delete;

	virtual void ChatOn();
	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	Dialogue* Chat;
	std::string Level;
	Player* PlayerInfo;
private:

};

