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

	//auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);

	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	auto backgroundObj = std::make_shared<dae::GameObject>();

	auto backgroundComp = std::make_shared<dae::TextureComponent>("background.tga");
	backgroundObj->AddComponent(backgroundComp);

	auto daeTextComp = std::make_shared<dae::TextureComponent>("logo.tga");
	daeTextComp->SetPosition(216, 180);
	backgroundObj->AddComponent(daeTextComp);


	auto fpsObj = std::make_shared<dae::GameObject>();

	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto fpsComp = std::make_shared<dae::FPSCounter>(fpsFont, 10.f, 10.f);
	fpsObj->AddComponent(fpsComp);


	auto textObj = std::make_shared<dae::GameObject>();
	
	auto textComp = std::make_shared<dae::TextComponent>("Programming 4 Assignment", fpsFont, 150.f, 50.f);
	textObj->AddComponent(textComp);

	//Sequence of addition defines depth value (WIP)
	scene.Add(backgroundObj);
	scene.Add(fpsObj);
	scene.Add(textObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}