#include "DiggerApp.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "DiggerCommands.h"
#include "FPSCounter.h"
#include "PlayerComponent.h"
#include "PlayerTextureComponent.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerHUD.h"
#include "SoundLocator.h"
#include "SoundSystem.h"
#include "GridMapComponent.h"
#include "CoinBagComponent.h"
#include "CoinBagTextureComponent.h"
#include "GemComponent.h"

void FH::DiggerApp::Run()
{
	FH::Minigin engine("../Data/");
	engine.Run([this]() { this->MakeDiggerScene(); });
}

void FH::DiggerApp::MakeDiggerScene()
{
	LoadTextures();
	LoadSounds();

	auto* scene = FH::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundObj = std::make_unique<FH::GameObject>();
	const auto pMap{ backgroundObj->AddComponent(std::make_unique<FH::GridMapComponent>(backgroundObj.get(),
		10, 15, 10.f, 10.f, 20.f, 0.f)).pComponent };

	auto fpsObj = std::make_unique<FH::GameObject>();
	fpsObj->AddComponent(std::make_unique<FH::FPSCounter>(fpsObj.get(), 12));


	auto digger{ std::make_unique<FH::GameObject>() };
	auto* pPlayerComp{ static_cast<PlayerComponent*>(
		digger->AddComponent(std::make_unique<FH::PlayerComponent>(digger.get(), 1, 1, pMap)).pComponent) };

	digger->AddComponent(std::make_unique<FH::PlayerTextureComponent>(digger.get(), pPlayerComp));


	auto moveUpController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(0.f, -1.f), pMap)) };
	auto moveDownController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(0.f, 1.f), pMap)) };
	auto moveLeftController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(-1.f, 0.f), pMap)) };
	auto moveRightController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(digger.get(), glm::vec2(1.f, 0.f), pMap)) };
	auto acceptController{ std::make_unique<FH::Action>(
		std::make_unique<FH::AcceptCommand>(digger.get())) };

	auto controllerActionMapping{ std::make_unique<FH::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, 
		{ std::make_pair(FH::Inputs::dPadUp, FH::InputType::buttonPressed) }, { SDL_SCANCODE_UP });
	controllerActionMapping->BindAction(moveDownController, 
		{ std::make_pair(FH::Inputs::dPadDown, FH::InputType::buttonPressed) }, { SDL_SCANCODE_DOWN });
	controllerActionMapping->BindAction(moveLeftController, 
		{ std::make_pair(FH::Inputs::dPadLeft, FH::InputType::buttonPressed) }, { SDL_SCANCODE_LEFT });
	controllerActionMapping->BindAction(moveRightController, 
		{ std::make_pair(FH::Inputs::dPadRight, FH::InputType::buttonPressed) }, { SDL_SCANCODE_RIGHT });
	controllerActionMapping->BindAction(acceptController, 
		{ std::make_pair(FH::Inputs::startButton, FH::InputType::buttonReleased) }, {});

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	FH::InputManager::GetInstance().AddController(controller);

	auto moneyBag{ std::make_unique<FH::GameObject>() };
	auto* pCoinBagComp{ static_cast<CoinBagComponent*>(
		moneyBag->AddComponent(std::make_unique<FH::CoinBagComponent>(moneyBag.get(), 2, 3, pMap, pPlayerComp)).pComponent) };
	moneyBag->AddComponent(std::make_unique<FH::CoinBagTextureComponent>(moneyBag.get(), pCoinBagComp));

	auto gems{ std::make_unique<FH::GameObject>() };
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 4, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 5, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 6, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 7, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 8, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 9, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 10, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 11, 3, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 4, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 5, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 6, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 7, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 8, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 9, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 10, 4, pMap, pPlayerComp));
	gems->AddComponent(std::make_unique<FH::GemComponent>(gems.get(), 11, 4, pMap, pPlayerComp));


	//auto controlsHelp{ std::make_unique<FH::GameObject>() };
	//controlsHelp->SetLocalPosition(glm::vec3(10.f, 50.f, 0.f));
	//controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Use the D-Pad to move", 0.f, 0.f, 18));
	//controlsHelp->AddComponent(std::make_unique<FH::TextComponent>(controlsHelp.get(), "Press START for teleport sound effect", 0.f, 20.f, 18));
	//
	//auto diggerHUD{ std::make_unique<FH::GameObject>() };
	//diggerHUD->SetLocalPosition(glm::vec3(10.f, 300.f, 0.f));
	//diggerHUD->AddComponent(std::make_unique<FH::PlayerHUD>(diggerHUD.get()));

	scene->Add(std::move(fpsObj));
	scene->Add(std::move(backgroundObj));
	scene->Add(std::move(digger));
	scene->Add(std::move(moneyBag));
	scene->Add(std::move(gems));

	auto& service{ SoundLocator::GetSoundService() };
	service.PlaySong("MainBGM", 0.4f, true);
}

void FH::DiggerApp::LoadTextures()
{
	auto& resourceManager{ FH::ResourceManager::GetInstance() };
	/////////////////////
	// Digger Textures //
	resourceManager.LoadTexture("DiggerSprites/LEFTDIG1.png", "LeftDig1");
	resourceManager.LoadTexture("DiggerSprites/LEFTDIG2.png", "LeftDig2");
	resourceManager.LoadTexture("DiggerSprites/LEFTDIG3.png", "LeftDig3");

	resourceManager.LoadTexture("DiggerSprites/RIGHTDIG1.png", "RightDig1");
	resourceManager.LoadTexture("DiggerSprites/RIGHTDIG2.png", "RightDig2");
	resourceManager.LoadTexture("DiggerSprites/RIGHTDIG3.png", "RightDig3");

	resourceManager.LoadTexture("DiggerSprites/DOWNDIG1.png", "DownDig1");
	resourceManager.LoadTexture("DiggerSprites/DOWNDIG2.png", "DownDig2");
	resourceManager.LoadTexture("DiggerSprites/DOWNDIG3.png", "DownDig3");

	resourceManager.LoadTexture("DiggerSprites/UPDIG1.png", "UpDig1");
	resourceManager.LoadTexture("DiggerSprites/UPDIG2.png", "UpDig2");
	resourceManager.LoadTexture("DiggerSprites/UPDIG3.png", "UpDig3");

	resourceManager.LoadTexture("DiggerSprites/DEADDIG.png", "DeadDig");
	/////////////////////

	//////////////////////
	// CoinBag Textures //
	resourceManager.LoadTexture("CoinBag/IDLECOINBAG.png", "IdleBag");

	resourceManager.LoadTexture("CoinBag/FALLINGCOINBAG.png", "FallingBag");

	resourceManager.LoadTexture("CoinBag/LEFTBAG.png", "LeftBag");
	resourceManager.LoadTexture("CoinBag/RIGHTBAG.png", "RightBag");

	resourceManager.LoadTexture("CoinBag/GOLD1.png", "Gold1");
	resourceManager.LoadTexture("CoinBag/GOLD2.png", "Gold2");
	resourceManager.LoadTexture("CoinBag/GOLD3.png", "Gold3");
	//////////////////////

	//////////////////
	// Gem Textures //
	resourceManager.LoadTexture("Gems/GEM.png", "Gem");
	//////////////////
}

void FH::DiggerApp::LoadSounds()
{
	SoundLocator::RegisterSystem(std::make_unique<SoundSystem>());
}
