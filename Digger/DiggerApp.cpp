#include <iostream>
#include <fstream>

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
#include "CoinBagComponent.h"
#include "CoinBagTextureComponent.h"
#include "GemComponent.h"

void FH::DiggerApp::Run()
{
	FH::Minigin engine("../Data/");
	engine.Run([this]() { this->MakeDiggerGame(); });
}

void FH::DiggerApp::MakeDiggerGame()
{
	LoadTextures();
	LoadSounds();

	CreateLevel("Level1Data");
	CreateLevel("Level2Data");
	CreateLevel("Level3Data");
	CreateLevel("Level4Data");

	auto& service{ SoundLocator::GetSoundService() };
	service.PlaySong("MainBGM", 0.4f, true);
}

void FH::DiggerApp::CreateLevel(std::string levelPath)
{
	auto gridData = ParseLevelFile(levelPath);

	auto* levelScene = FH::SceneManager::GetInstance().CreateScene("Level" + std::to_string(m_LevelIdx + 1));

	auto mapObj = std::make_unique<FH::GameObject>();
	auto* pMap{ 
		static_cast<GridMapComponent*>(
		mapObj->AddComponent(std::make_unique<FH::GridMapComponent>(mapObj.get(), gridData, mapColors[m_LevelIdx % COLORAMOUNT],
		10.f, 10.f, 20.f, 0.f)).pComponent) 
	};

	auto digger{ std::make_unique<FH::GameObject>() };
	auto* pPlayerComp{ 
		static_cast<PlayerComponent*>(
		digger->AddComponent(std::make_unique<FH::PlayerComponent>(digger.get(), pMap)).pComponent) 
	};
	digger->AddComponent(std::make_unique<FH::PlayerTextureComponent>(digger.get(), pPlayerComp));

	MapControls(digger.get(), pMap);

	levelScene->Add(std::move(mapObj));
	levelScene->Add(std::move(digger));

	for (int i{}; i < static_cast<int>(gridData.mapData.size()); ++i)
	{
		auto* cell = pMap->GetCell(i);

		if (cell->m_HasBag)
		{
			auto moneyBag{ std::make_unique<FH::GameObject>() };
			auto* pCoinBagComp{ 
				static_cast<CoinBagComponent*>(moneyBag->AddComponent(std::make_unique<FH::CoinBagComponent>(
					moneyBag.get(), cell->m_Col, cell->m_Row, pMap, pPlayerComp)).pComponent)
			};
			moneyBag->AddComponent(std::make_unique<FH::CoinBagTextureComponent>(moneyBag.get(), pCoinBagComp));

			levelScene->Add(std::move(moneyBag));
			continue;
		}

		if (cell->m_HasGem)
		{
			auto gem{ std::make_unique<FH::GameObject>() };
			gem->AddComponent(std::make_unique<FH::GemComponent>(gem.get(), cell->m_Col, cell->m_Row, pMap, pPlayerComp));

			levelScene->Add(std::move(gem));
			continue;
		}

		if (cell->m_HasPlayer)
		{
			pPlayerComp->SetCellPos(cell->m_Col, cell->m_Row);
			continue;
		}
	}
	++m_LevelIdx;
}

FH::GenData FH::DiggerApp::ParseLevelFile(std::string levelPath)
{
	std::ifstream dataFile{ "../Data/Levels/" + levelPath + ".txt" };

	if (!dataFile)
		throw std::runtime_error("Could not find level file!");

	std::vector<int> mapGen{};
	int cols{};
	int rows{};

	while (!dataFile.eof())
	{
		std::string rowData{};
		std::getline(dataFile, rowData, '\n');

		//Skip Comment or empty line
		if (rowData.find('#') != std::string::npos || rowData.empty())
			continue;

		for (int i{}; i < static_cast<int>(rowData.size()); ++i)
		{
			char rowChar = rowData[i];

			switch (rowChar)
			{
			case 'E':
				mapGen.push_back(0);
				break;
			case 'V':
				mapGen.push_back(1);
				break;
			case 'M':
				mapGen.push_back(2);
				break;
			case 'G':
				mapGen.push_back(3);
				break;
			case 'P':
				mapGen.push_back(4);
				break;
			default:
				break;
			}
		}

		++rows;
		cols = static_cast<int>(rowData.size());
	}

	if (rows * cols == static_cast<int>(mapGen.size()))
		return { mapGen, rows, cols };
	else
		throw std::runtime_error("Level file had a faulty format!");
}

void FH::DiggerApp::MapControls(GameObject* controlledObj, GridMapComponent* pMap)
{
	auto moveUpController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(controlledObj, glm::vec2(0.f, -1.f), pMap)) };
	auto moveDownController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(controlledObj, glm::vec2(0.f, 1.f), pMap)) };
	auto moveLeftController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(controlledObj, glm::vec2(-1.f, 0.f), pMap)) };
	auto moveRightController{ std::make_unique<FH::Action>(
		std::make_unique<FH::MoveCommand>(controlledObj, glm::vec2(1.f, 0.f), pMap)) };
	auto acceptController{ std::make_unique<FH::Action>(
		std::make_unique<FH::AcceptCommand>(controlledObj)) };

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
		{ std::make_pair(FH::Inputs::startButton, FH::InputType::buttonReleased) }, { });

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	InputManager::GetInstance().AddController(controller);
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
