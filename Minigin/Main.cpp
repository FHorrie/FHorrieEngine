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
	auto bigger{ std::make_unique<FH::GameObject>() };
	bigger->SetLocalPosition(glm::vec3(100.f, 100.f, 0.f));
	bigger->AddComponent(std::make_unique<FH::AttackComponent>(bigger.get(), Rect{0,0,16,16}));
	bigger->AddComponent(std::make_unique<FH::TextureComponent>(bigger.get(), "CRBIG1.png"));

	auto digger{ std::make_unique<FH::GameObject>() };
	digger->SetLocalPosition(glm::vec3(150.f, 100.f, 0.f));
	digger->AddComponent(std::make_unique<FH::AttackComponent>(digger.get(), Rect{0,0,16,16}));
	digger->AddComponent(std::make_unique<FH::TextureComponent>(digger.get(), "CLDIG1.png"));

	auto moveUpController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(bigger.get(), glm::vec3(0.f, -1.f, 0.f), 200.f)) };
	auto moveDownController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(bigger.get(), glm::vec3(0.f, 1.f, 0.f), 200.f)) };
	auto moveLeftController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(bigger.get(), glm::vec3(-1.f, 0.f, 0.f), 200.f)) };
	auto moveRightController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(bigger.get(), glm::vec3(1.f, 0.f, 0.f), 200.f)) };
	auto attackController{ std::make_unique<FH::Action>(std::make_unique<FH::AttackCommand>(bigger.get())) };
	auto smallPointsController{ std::make_unique<FH::Action>(std::make_unique<FH::GainScoreCommand>(bigger.get(), false)) };
	auto bigPointsController{ std::make_unique<FH::Action>(std::make_unique<FH::GainScoreCommand>(bigger.get(), true)) };

	auto moveUpKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, -1.f, 0.f), 400.f)) };
	auto moveDownKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, 1.f, 0.f), 400.f)) };
	auto moveLeftKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(-1.f, 0.f, 0.f), 400.f)) };
	auto moveRightKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(1.f, 0.f, 0.f), 400.f)) };
	auto attackKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::AttackCommand>(digger.get())) };
	auto smallPointsKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::GainScoreCommand>(bigger.get(), false)) };
	auto bigPointsKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::GainScoreCommand>(bigger.get(), true)) };

	auto controllerActionMapping{ std::make_unique<FH::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, { std::make_pair(FH::Inputs::dPadUp, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveDownController, { std::make_pair(FH::Inputs::dPadDown, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveLeftController, { std::make_pair(FH::Inputs::dPadLeft, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveRightController, { std::make_pair(FH::Inputs::dPadRight, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(attackController, { std::make_pair(FH::Inputs::buttonWest, FH::InputType::buttonDown) }, {});
	controllerActionMapping->BindAction(smallPointsController, { std::make_pair(FH::Inputs::buttonEast, FH::InputType::buttonDown) }, {});
	controllerActionMapping->BindAction(bigPointsController, { std::make_pair(FH::Inputs::buttonSouth, FH::InputType::buttonDown) }, {});

	auto keyboardActionMapping{ std::make_unique<FH::InputMapping>() };
	keyboardActionMapping->BindAction(moveUpKeyboard, {}, { SDL_SCANCODE_W });
	keyboardActionMapping->BindAction(moveDownKeyboard, {}, { SDL_SCANCODE_S });
	keyboardActionMapping->BindAction(moveLeftKeyboard, {}, { SDL_SCANCODE_A });
	keyboardActionMapping->BindAction(moveRightKeyboard, {}, { SDL_SCANCODE_D });
	keyboardActionMapping->BindAction(attackKeyboard, {}, { SDL_SCANCODE_F });
	keyboardActionMapping->BindAction(smallPointsKeyboard, {}, { SDL_SCANCODE_Q });
	keyboardActionMapping->BindAction(bigPointsKeyboard, {}, { SDL_SCANCODE_E });

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	auto keyboard{ std::make_unique<FH::Controller>() };
	keyboard->StoreInputMapping(keyboardActionMapping);

	FH::InputManager::GetInstance().AddController(controller);
	FH::InputManager::GetInstance().AddController(keyboard);

	auto controllsHelp{ std::make_unique<FH::GameObject>() };
	controllsHelp->SetLocalPosition(glm::vec3(10.f, 50.f, 0.f));
	controllsHelp->AddComponent(std::make_unique<FH::TextComponent>(controllsHelp.get(), "Use the D-Pad to move Bigger, X to damage, A/B for points", 0.f, 0.f, 16));
	controllsHelp->AddComponent(std::make_unique<FH::TextComponent>(controllsHelp.get(), "Use WASD to move Digger, F to damage, Q/E for points", 0.f, 20.f, 16));

	auto biggerHUD{ std::make_unique<FH::GameObject>() };
	biggerHUD->SetLocalPosition(glm::vec3(10.f, 360.f, 0.f));
	biggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(biggerHUD.get()));
	biggerHUD->AddComponent(std::make_unique<FH::SteamAchievementComponent>(biggerHUD.get(), g_SteamAchievements));
	bigger->GetComponentOfType<FH::AttackComponent>()->AddObserver(biggerHUD->GetComponentOfType<FH::PlayerHUD>());
	bigger->GetComponentOfType<FH::AttackComponent>()->AddObserver(biggerHUD->GetComponentOfType<FH::SteamAchievementComponent>());
	auto diggerHUD{ std::make_unique<FH::GameObject>() };
	diggerHUD->SetLocalPosition(glm::vec3(10.f, 300.f, 0.f));
	diggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(diggerHUD.get()));
	diggerHUD->AddComponent(std::make_unique<FH::SteamAchievementComponent>(diggerHUD.get(), g_SteamAchievements));
	digger->GetComponentOfType<FH::AttackComponent>()->AddObserver(diggerHUD->GetComponentOfType<FH::PlayerHUD>());
	digger->GetComponentOfType<FH::AttackComponent>()->AddObserver(diggerHUD->GetComponentOfType<FH::SteamAchievementComponent>());

	scene.Add(std::move(bigger));
	scene.Add(std::move(digger));

	scene.Add(std::move(controllsHelp));
	scene.Add(std::move(biggerHUD));
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