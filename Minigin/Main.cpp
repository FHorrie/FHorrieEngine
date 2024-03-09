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

	auto backgroundObj = std::make_unique<dae::GameObject>();
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj.get(), "background.tga"));
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj.get(), "logo.tga", 216.f, 180.f));

	auto textObj = std::make_unique<dae::GameObject>();
	textObj->AddComponent(std::make_unique<dae::TextComponent>(textObj.get(), "Programming 4 Assignment", 150.f, 50.f));

	auto fpsObj = std::make_unique<dae::GameObject>();
	fpsObj->AddComponent(std::make_unique<dae::FPSCounter>(fpsObj.get()));

	auto posObj = std::make_unique<dae::GameObject>();
	posObj->SetLocalPosition(glm::vec3(200.f, 350.f, 0.f));

	auto rotationObj = std::make_unique<dae::GameObject>();
	rotationObj->AddComponent(std::make_unique<dae::RotationComponent>(rotationObj.get(), glm::vec3(100.f, 0.f, 0.f), 1.f));
	rotationObj->AddComponent(std::make_unique<dae::TextureComponent>(rotationObj.get(), "pacman.png"));

	auto orbitObj = std::make_unique<dae::GameObject>();
	orbitObj->AddComponent(std::make_unique<dae::RotationComponent>(orbitObj.get(), glm::vec3(0.f, 50.f, 0.f), 3.f));
	orbitObj->AddComponent(std::make_unique<dae::TextureComponent>(orbitObj.get(), "pacman.png"));

	auto orbit1Obj = std::make_unique<dae::GameObject>();
	orbit1Obj->AddComponent(std::make_unique<dae::RotationComponent>(orbit1Obj.get(), glm::vec3(70.f, 70.f, 0.f), -5.f));
	orbit1Obj->AddComponent(std::make_unique<dae::TextureComponent>(orbit1Obj.get(), "pacman.png"));

	posObj->AddChild(rotationObj.get());
	rotationObj->AddChild(orbitObj.get());
	orbitObj->AddChild(orbit1Obj.get());

	//Sequence of addition defines depth value (WIP)
	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(textObj));
	scene.Add(std::move(fpsObj));
	scene.Add(std::move(posObj));
	scene.Add(std::move(rotationObj));
	scene.Add(std::move(orbitObj));
	scene.Add(std::move(orbit1Obj));
}

int main(int, char*[]) {
	srand(int(time(nullptr)));
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}