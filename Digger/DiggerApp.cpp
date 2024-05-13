#include "DiggerApp.h"
#include "Minigin.h"
#include "TextureComponent.h"
#include "DiggerCommands.h"
#include "FPSCounter.h"
#include "PlayerComponent.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerHUD.h"
#include "SoundLocator.h"
#include "SoundSystem.h"
#include "GridMapComponent.h"
#include "MoneyBagComponent.h"

void FH::DiggerApp::Run()
{
	FH::Minigin engine("../Data/");
	engine.Run([this]() { this->LoadAll(); });
}

void FH::DiggerApp::LoadAll()
{
	auto& scene = FH::SceneManager::GetInstance().CreateScene("Demo");
	LoadSounds();

	auto backgroundObj = std::make_unique<FH::GameObject>();
	backgroundObj->AddComponent(std::make_unique<FH::GridMapComponent>(backgroundObj.get(), 10, 15, 10.f, 10.f, 20.f, 0.f));

	//auto fpsObj = std::make_unique<FH::GameObject>();
	//fpsObj->AddComponent(std::make_unique<FH::FPSCounter>(fpsObj.get()));


	auto digger{ std::make_unique<FH::GameObject>() };
	digger->AddComponent(std::make_unique<FH::PlayerComponent>(digger.get(), 1, 1,
		backgroundObj->GetComponentOfType<GridMapComponent>()));
	digger->AddComponent(std::make_unique<FH::TextureComponent>(digger.get(), "DiggerSprites/LEFTDIG1.png"));

	auto moveUpController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(0.f, -1.f), 200.f)) };
	auto moveDownController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(0.f, 1.f), 200.f)) };
	auto moveLeftController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(-1.f, 0.f), 200.f)) };
	auto moveRightController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(1.f, 0.f), 200.f)) };
	auto acceptController{ std::make_unique<FH::Action>(
		std::make_unique<FH::AcceptCommand>(digger.get())) };

	auto controllerActionMapping{ std::make_unique<FH::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, { std::make_pair(FH::Inputs::dPadUp, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveDownController, { std::make_pair(FH::Inputs::dPadDown, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveLeftController, { std::make_pair(FH::Inputs::dPadLeft, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveRightController, { std::make_pair(FH::Inputs::dPadRight, FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(acceptController, { std::make_pair(FH::Inputs::startButton, FH::InputType::buttonReleased) }, {});

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	FH::InputManager::GetInstance().AddController(controller);

	auto moneyBag{ std::make_unique<FH::GameObject>() };
	moneyBag->AddComponent(std::make_unique<FH::MoneyBagComponent>(moneyBag.get(), 3, 3, 
		backgroundObj->GetComponentOfType<GridMapComponent>(), 
		digger->GetComponentOfType<PlayerComponent>()));
	moneyBag->AddComponent(std::make_unique<FH::TextureComponent>(moneyBag.get(), "CoinBag/IDLECOINBAG.png"));

	//auto controlsHelp{ std::make_unique<FH::GameObject>() };
	//controlsHelp->SetLocalPosition(glm::vec3(10.f, 50.f, 0.f));
	//controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Use the D-Pad to move", 0.f, 0.f, 18));
	//controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Press START for teleport sound effect", 0.f, 20.f, 18));

	//auto diggerHUD{ std::make_unique<FH::GameObject>() };
	//diggerHUD->SetLocalPosition(glm::vec3(10.f, 300.f, 0.f));
	//diggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(diggerHUD.get()));

	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(digger));
	scene.Add(std::move(moneyBag));

	//scene.Add(std::move(controlsHelp));
	//scene.Add(std::move(fpsObj));

}

void FH::DiggerApp::LoadSounds()
{
	SoundLocator::RegisterSystem(std::make_unique<SoundSystem>());
}
