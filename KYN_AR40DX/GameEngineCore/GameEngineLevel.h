#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <list>
#include <map>

// ���� : ȭ��(Ÿ��Ʋ ȭ��, �÷��� ȭ��, �κ��丮 ȭ��)
class GameEngineCore;
class GameEngineActor;
class GameEngineCamera;
class GameEngineRenderer;
class GameEngineTransform;
class GameEngineCameraActor;
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend GameEngineCore;
	friend GameEngineActor;
	friend GameEngineCamera;
	friend GameEngineRenderer;
	// ������ ������� �󸶳� �����־����� �ð��� ��� �ְ� �Ѵ�.

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	GameEngineCamera* GetMainCamera()
	{
		return MainCamera;
	}

	GameEngineTransform& GetMainCameraActorTransform();

	//template<typename ReturnType, typename ActorType, typename GroupIndexType>
	//ReturnType* CreateActor(GroupIndexType _ObjectGroupIndex)
	//{
	//	return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	//}

	template<typename ActorType, typename GroupIndexType>
	ActorType* CreateActor(GroupIndexType _ObjectGroupIndex)
	{
		return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ActorType>
	ActorType* CreateActor(const std::string _Name, int _ObjectGroupIndex = 0)
	{
		CreateActor(_ObjectGroupIndex);
	}

	template<typename ActorType>
	ActorType* CreateActor(int _ObjectGroupIndex = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->SetOrder(_ObjectGroupIndex);
		NewActor->Start();

		// AllActors[_ObjectGroupIndex]�� ����ϸ�
		// ������ ���������� ������
		// ã�Ƽ� �������ش�.
		std::list<GameEngineActor*>& Group = AllActors[_ObjectGroupIndex];

		Group.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}


	template<typename GroupIndexType>
	std::list<GameEngineActor*> GetGroup(GroupIndexType _ObjectGroupIndex)
	{
		return AllActors[static_cast<int>(_ObjectGroupIndex)];
	}

	std::list<GameEngineActor*> GetGroup(int _ObjectGroupIndex)
	{
		return AllActors[_ObjectGroupIndex];
	}

	template<typename ObjectType, typename GroupIndexType>
	std::list<ObjectType*> GetConvertToGroup(GroupIndexType _ObjectGroupIndex)
	{
		return GetConvertToGroup<ObjectType>(static_cast<int>(_ObjectGroupIndex));
	}


	template<typename ObjectType>
	std::list<ObjectType*> GetConvertToGroup(int _ObjectGroupIndex)
	{
		std::list<ObjectType*> Result;
		for (GameEngineActor* Object : AllActors[_ObjectGroupIndex])
		{
			Result.push_back(dynamic_cast<ObjectType*>(Object));
		}

		return Result;
	}

protected:




private:
	// 0�� �׷� �÷��̾�
	// 1�� �׷� ����
	// 2�� �׷�
	std::map<int, std::list<GameEngineActor*>> AllActors;
	std::list<GameEngineUpdateObject*> DeleteObject;

	void ActorUpdate(float _DelataTime);

	void LevelUpdate(float DeltaTime);

	void RemoveActor(GameEngineActor* _Actor);

private:
	// 0�� ��׶���
	// 1�� �÷��̾�
	// 2�� UI
	GameEngineCamera* MainCamera;

	GameEngineCamera* UIMainCamera;

	void PushCamera(GameEngineCamera* _Camera);

	void PushRenderer(GameEngineRenderer* _Renderer);

	void Render(float _DelataTime);

	void Release(float _DelataTime);
};
