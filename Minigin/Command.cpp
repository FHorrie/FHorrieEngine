#include "Command.h"

using namespace dae;

void MoveUp::Execute(dae::GameObject* gameObject)
{
	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
	if (TransformComp)
		TransformComp->SetPosValsToIncrease(glm::vec3(0.f, -1.f, 0.f));
}

void MoveDown::Execute(dae::GameObject* gameObject)
{
	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
	if (TransformComp)
		TransformComp->SetPosValsToIncrease(glm::vec3(0.f, 1.f, 0.f));
}

void MoveLeft::Execute(dae::GameObject* gameObject)
{
	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
	if (TransformComp)
		TransformComp->SetPosValsToIncrease(glm::vec3(-1.f, 0.f, 0.f));
}

void MoveRight::Execute(dae::GameObject* gameObject)
{
	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
	if (TransformComp)
		TransformComp->SetPosValsToIncrease(glm::vec3(1.f, 0.f, 0.f));
}