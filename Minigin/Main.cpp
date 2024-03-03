#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSCounter.h"
#include "TransformComponent.h"
#include "RotationComponent.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObj = std::make_shared<dae::GameObject>();
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj, "background.tga"));
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj, "logo.tga", 216.f, 180.f));

	auto textObj = std::make_shared<dae::GameObject>();
	textObj->AddComponent(std::make_unique<dae::TextComponent>(textObj, "Programming 4 Assignment", 150.f, 50.f));

	auto fpsObj = std::make_shared<dae::GameObject>();
	fpsObj->AddComponent(std::make_unique<dae::FPSCounter>(fpsObj));

	auto posObj = std::make_shared<dae::GameObject>();
	posObj->SetLocalPosition(glm::vec3(200.f, 350.f, 0.f));

	auto rotationObj = std::make_shared<dae::GameObject>();
	rotationObj->AddComponent(std::make_unique<dae::RotationComponent>(rotationObj, glm::vec3(30.f, 30.f, 0.f), 4.f));
	rotationObj->AddComponent(std::make_unique<dae::TextureComponent>(rotationObj, "pacman.png"));

	auto orbitObj = std::make_shared<dae::GameObject>();
	orbitObj->AddComponent(std::make_unique<dae::RotationComponent>(orbitObj, glm::vec3(50.f, 50.f, 0.f), 6.f));
	orbitObj->AddComponent(std::make_unique<dae::TextureComponent>(orbitObj, "pacman.png"));

	auto orbit1Obj = std::make_shared<dae::GameObject>();
	orbit1Obj->AddComponent(std::make_unique<dae::RotationComponent>(orbit1Obj, glm::vec3(30.f, 30.f, 0.f), 10.f));
	orbit1Obj->AddComponent(std::make_unique<dae::TextureComponent>(orbit1Obj, "pacman.png"));

	posObj->AddChild(rotationObj);
	rotationObj->AddChild(orbitObj);
	orbitObj->AddChild(orbit1Obj);

	//Sequence of addition defines depth value (WIP)
	scene.Add(backgroundObj);
	scene.Add(textObj);
	scene.Add(fpsObj);
	scene.Add(posObj);
	scene.Add(rotationObj);
	scene.Add(orbitObj);
	scene.Add(orbit1Obj);
}

int main(int, char*[]) {
	srand(int(time(nullptr)));
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}