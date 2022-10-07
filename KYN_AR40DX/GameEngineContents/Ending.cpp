#include "PreCompile.h"
#include "Ending.h"
#include "EndingLogo.h"
#include "Enums.h"
#include "Black.h"
#include "Mouse.h"
Ending::Ending()
{

}

Ending::~Ending()
{

}

void Ending::Start()
{
	EndingActor = CreateActor<EndingLogo>(GameObjectGroup::UI);

	B = CreateActor<Black>(OBJECTORDER::Black);
	B->GetTransform().SetWorldPosition({ 0,0,-500 });

	Cursor = CreateActor<Mouse>(OBJECTORDER::UI);
}

void Ending::Update(float _DeltaTime)
{
	BlackTimeOut();
}

void Ending::End()
{
}

void Ending::LevelStartEvent()
{
	LevelIn = true;
}
