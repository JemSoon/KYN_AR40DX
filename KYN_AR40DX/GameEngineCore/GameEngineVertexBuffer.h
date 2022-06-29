#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"
#include <vector>
#include <string>
#include <map>
#include <list>

// 설명 :
class GameEngineVertexBuffer : public GameEngineRes<GameEngineVertexBuffer>
{
public:
	friend GameEngineRes<GameEngineVertexBuffer>;

public:
	template<typename VertexType>
	static GameEngineVertexBuffer* Create(const std::string& _Name, const std::vector<float4>& _Vertex)
	{
		return Create(_Name, &_Vertex[0], _Vertex.size() * sizeof(VertexType));
	}
	static GameEngineVertexBuffer* Create(const std::string& _Name, const void* _Data, size_t _Size);
	//static GameEngineVertexBuffer* Create(const std::vector<float4>& _Vertex);

private:
	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;

protected:


private:
	D3D11_BUFFER_DESC BufferDesc; //버퍼를 만들기 위한 정보 스트럭트

	D3D11_SUBRESOURCE_DATA Data;

	ID3D11Buffer* Buffer;

};

