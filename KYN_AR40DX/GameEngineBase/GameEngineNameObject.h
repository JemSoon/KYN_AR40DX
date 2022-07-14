#pragma once
#include <string>

// 설명 :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	// 그냥 std::string으로 하면 값이 복사가 되면서 문제가 많아진다.
	inline void SetName(const std::string& _Name)
	{
		ObjectName_ = _Name;
	}

	// 어마어마 싫어하는 사람들이 이습니다.
	// 필요할때 써야겠죠.
	std::string GetNameCopy() const
	{
		return ObjectName_;
	}

	const std::string& GetNameConstRef()
	{
		return ObjectName_;
	}

	const char* GetNameConstPtr()
	{
		return ObjectName_.c_str();
	}


protected:

private:
	std::string ObjectName_;

};

