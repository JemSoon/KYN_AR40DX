#include "PreCompile.h"
#include "CharacterObject.h"

CharacterObject::CharacterObject()
	:Renderer(nullptr)
	,Speed(100.0)
{

}

CharacterObject::~CharacterObject()
{

}

void CharacterObject::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
}

void CharacterObject::Update(float _DeltaTime)
{
}

