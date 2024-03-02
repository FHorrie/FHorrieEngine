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

	//Sequence of addition defines depth value (WIP)
	scene.Add(backgroundObj);
	scene.Add(textObj);
	scene.Add(fpsObj);
}

int main(int, char*[]) {
	srand(int(time(nullptr)));
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}