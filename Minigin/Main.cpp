#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <steam_api.h>
#include <iostream>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "GlobalSteamAch.h"
#include "GlobalSteamVar.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSCounter.h"
#include "TransformComponent.h"
#include "RotationComponent.h"
#include "AttackComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "Action.h"
#include "Command.h"
#include "InputMapping.h"
#include "BaseInputDevice.h"
#include "Controller.h"
#include "PlayerHUD.h"
#include "SteamAchievements.h"
#include "SteamAchievementComponent.h"

void LoadBackground(FH::Scene& scene);
void AddPlayerInput(FH::Scene& scene);

void load()
{
	auto& scene = FH::SceneManager::GetInstance().CreateScene("Demo");
	LoadBackground(scene);
	AddPlayerInput(scene);
}

void LoadBackground(FH::Scene& scene)
{
	auto backgroundObj = std::make_unique<FH::GameObject>();
	backgroundObj->AddComponent(std::make_unique<FH::TextureComponent>(backgroundObj.get(), "background.tga"));

	auto fpsObj = std::make_unique<FH::GameObject>();
	fpsObj->AddComponent(std::make_unique<FH::FPSCounter>(fpsObj.get()));

	//Sequence of addition defines depth value (WIP)
	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(fpsObj));
}

void AddPlayerInput(FH::Scene& scene)
{
	auto digger{ std::make_unique<FH::GameObject>() };
	digger->SetLocalPosition(glm::vec3(150.f, 100.f, 0.f));
	digger->AddComponent(std::make_unique<FH::AttackComponent>(digger.get(), Rect{0,0,16,16}));
	digger->AddComponent(std::make_unique<FH::TextureComponent>(digger.get(), "CLDIG1.png"));

	auto moveUpController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, -1.f, 0.f), 200.f)) };
	auto moveDownController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, 1.f, 0.f), 200.f)) };
	auto moveLeftController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(-1.f, 0.f, 0.f), 200.f)) };
	auto moveRightController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(1.f, 0.f, 0.f), 200.f)) };

	auto controllerActionMapping{ std::make_unique<FH::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, { std::make_pair(FH::Inputs::dPadUp, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveDownController, { std::make_pair(FH::Inputs::dPadDown, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveLeftController, { std::make_pair(FH::Inputs::dPadLeft, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveRightController, { std::make_pair(FH::Inputs::dPadRight, FH::InputType::buttonPressed) }, {});

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	FH::InputManager::GetInstance().AddController(controller);

	auto controlsHelp{ std::make_unique<FH::GameObject>() };
	controlsHelp->SetLocalPosition(glm::vec3(10.f, 50.f, 0.f));
	controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Use the D-Pad to move Bigger", 0.f, 0.f, 16));

	auto diggerHUD{ std::make_unique<FH::GameObject>() };
	diggerHUD->SetLocalPosition(glm::vec3(10.f, 300.f, 0.f));
	diggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(diggerHUD.get()));
	diggerHUD->AddComponent(std::make_unique<FH::SteamAchievementComponent>(diggerHUD.get(), g_SteamAchievements));
	digger->GetComponentOfType<FH::AttackComponent>()->AddObserver(diggerHUD->GetComponentOfType<FH::PlayerHUD>());
	digger->GetComponentOfType<FH::AttackComponent>()->AddObserver(diggerHUD->GetComponentOfType<FH::SteamAchievementComponent>());

	scene.Add(std::move(digger));
	scene.Add(std::move(controlsHelp));
	scene.Add(std::move(diggerHUD));
}

int main(int, char*[]) 
{

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
		g_SteamAchievements = new CSteamAchievements(g_Achievements, 4);
	}


	FH::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();

	if (g_SteamAchievements)
		delete g_SteamAchievements;

    return 0;
}