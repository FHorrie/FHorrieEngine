#include "DiggerApp.h"
#include "Minigin.h"
#include "TextureComponent.h"
#include "FPSCounter.h"
#include "AttackComponent.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerHUD.h"
#include "SoundLocator.h"
#include "SoundSystem.h"

void FH::DiggerApp::Run()
{
	FH::Minigin engine("../Data/");
	engine.Run([this]() { this->LoadAll(); });
}

void FH::DiggerApp::LoadAll()
{
	auto& scene = FH::SceneManager::GetInstance().CreateScene("Demo");
	LoadSounds();
	LoadBackground(scene);
	AddPlayerInput(scene);
}

void FH::DiggerApp::LoadSounds()
{
	SoundLocator::RegisterSystem(std::make_unique<SoundSystem>());
}

void FH::DiggerApp::LoadBackground(Scene& scene)
{
	auto backgroundObj = std::make_unique<FH::GameObject>();
	backgroundObj->AddComponent(std::make_unique<FH::TextureComponent>(backgroundObj.get(), "background.tga"));

	auto fpsObj = std::make_unique<FH::GameObject>();
	fpsObj->AddComponent(std::make_unique<FH::FPSCounter>(fpsObj.get()));

	//Sequence of addition defines depth value (WIP)
	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(fpsObj));
}

void FH::DiggerApp::AddPlayerInput(FH::Scene& scene)
{
	auto digger{ std::make_unique<FH::GameObject>() };
	digger->SetLocalPosition(glm::vec3(150.f, 100.f, 0.f));
	digger->AddComponent(std::make_unique<FH::AttackComponent>(digger.get(), Rect{ 0,0,16,16 }));
	digger->AddComponent(std::make_unique<FH::TextureComponent>(digger.get(), "CLDIG1.png"));

	auto moveUpController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, -1.f, 0.f), 200.f)) };
	auto moveDownController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(0.f, 1.f, 0.f), 200.f)) };
	auto moveLeftController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(-1.f, 0.f, 0.f), 200.f)) };
	auto moveRightController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(digger.get(), glm::vec3(1.f, 0.f, 0.f), 200.f)) };
	auto acceptController{ std::make_unique<FH::Action>(std::make_unique<FH::AcceptCommand>(digger.get())) };

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

	auto controlsHelp{ std::make_unique<FH::GameObject>() };
	controlsHelp->SetLocalPosition(glm::vec3(10.f, 50.f, 0.f));
	controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Use the D-Pad to move", 0.f, 0.f, 18));
	controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Press START for teleport sound effect", 0.f, 20.f, 18));

	//auto diggerHUD{ std::make_unique<FH::GameObject>() };
	//diggerHUD->SetLocalPosition(glm::vec3(10.f, 300.f, 0.f));
	//diggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(diggerHUD.get()));

	scene.Add(std::move(digger));
	scene.Add(std::move(controlsHelp));
}