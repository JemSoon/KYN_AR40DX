#pragma once
#include <GameEngineCore/GameEngineStatusWindow.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class Player;
class LevelParent;
class ContentsGUI : public GameEngineStatusWindow
{
public:
	//디폴트 생성자
	ContentsGUI();
	//디폴트 소멸자
	~ContentsGUI();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	ContentsGUI(const ContentsGUI& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	ContentsGUI(ContentsGUI&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	ContentsGUI& operator=(const ContentsGUI& _Other) = delete;
	ContentsGUI& operator=(ContentsGUI&& _Other) noexcept = delete;


protected:
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
private:
	Player* PlayerInfo;
};

