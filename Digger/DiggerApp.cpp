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
#include "ScoreComponent.h"
#include "LivesComponent.h"

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

	SoundLocator::GetSoundService().PlaySong("MainBGM", 0.4f, true);
}

void FH::DiggerApp::CreateLevel(std::string levelPath)
{
	auto gridData = ParseLevelFile(levelPath);

	auto* levelScene = SceneManager::GetInstance().CreateScene("Level" + std::to_string(m_LevelIdx + 1));

	auto mapObj = std::make_unique<GameObject>();
	auto* pMap{ 
		static_cast<GridMapComponent*>(
		mapObj->AddComponent(std::make_unique<GridMapComponent>(mapObj.get(), gridData, mapColors[m_LevelIdx % COLORAMOUNT],
		10.f, 10.f, 20.f, 0.f)).pComponent) 
	};

	auto digger{ std::make_unique<GameObject>() };
	auto* pPlayerComp{ 
		static_cast<PlayerComponent*>(
		digger->AddComponent(std::make_unique<PlayerComponent>(digger.get(), pMap)).pComponent) 
	};
	digger->AddComponent(std::make_unique<PlayerTextureComponent>(digger.get(), pPlayerComp));

	MapControls(digger.get(), pMap, true, 0);

	levelScene->Add(std::move(mapObj));
	levelScene->Add(std::move(digger));

	auto score{ std::make_unique<GameObject>() };
	score->AddComponent(std::make_unique<ScoreComponent>(score.get(), pPlayerComp));

	auto lives{ std::make_unique<GameObject>() };
	lives->AddComponent(std::make_unique<LivesComponent>(lives.get(), pPlayerComp));

	levelScene->Add(std::move(score));
	levelScene->Add(std::move(lives));

	for (int i{}; i < static_cast<int>(gridData.mapData.size()); ++i)
	{
		auto* cell = pMap->GetCell(i);

		if (cell->m_HasBag)
		{
			auto moneyBag{ std::make_unique<GameObject>() };
			auto* pCoinBagComp{ 
				static_cast<CoinBagComponent*>(moneyBag->AddComponent(std::make_unique<CoinBagComponent>(
					moneyBag.get(), cell->m_Col, cell->m_Row, pMap, pPlayerComp)).pComponent)
			};
			moneyBag->AddComponent(std::make_unique<CoinBagTextureComponent>(moneyBag.get(), pCoinBagComp));

			levelScene->Add(std::move(moneyBag));
			continue;
		}

		if (cell->m_HasGem)
		{
			auto gem{ std::make_unique<GameObject>() };
			gem->AddComponent(std::make_unique<GemComponent>(gem.get(), cell->m_Col, cell->m_Row, pMap, pPlayerComp));

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

void FH::DiggerApp::MapControls(GameObject* controlledObj, GridMapComponent* pMap, bool useKeyboard, int controllerIdx)
{
	auto moveUp{ std::make_unique<Action>(
		std::make_unique<MoveCommand>(controlledObj, glm::vec2(0.f, -1.f), pMap)) };
	auto moveDown{ std::make_unique<Action>(
		std::make_unique<MoveCommand>(controlledObj, glm::vec2(0.f, 1.f), pMap)) };
	auto moveLeft{ std::make_unique<Action>(
		std::make_unique<MoveCommand>(controlledObj, glm::vec2(-1.f, 0.f), pMap)) };
	auto moveRight{ std::make_unique<Action>(
		std::make_unique<MoveCommand>(controlledObj, glm::vec2(1.f, 0.f), pMap)) };
	auto attack{ std::make_unique<Action>(
		std::make_unique<AttackCommand>(controlledObj)) };

	auto actionMapping{ std::make_unique<InputMapping>() };

	std::vector<SDL_Scancode> upK{};
	std::vector<SDL_Scancode> downK{};
	std::vector<SDL_Scancode> leftK{};
	std::vector<SDL_Scancode> rightK{};
	std::vector<SDL_Scancode> attackK{};

	if (useKeyboard)
	{
		upK = { SDL_SCANCODE_UP, SDL_SCANCODE_W };
		downK = { SDL_SCANCODE_DOWN, SDL_SCANCODE_S };
		leftK = { SDL_SCANCODE_LEFT, SDL_SCANCODE_A };
		rightK = { SDL_SCANCODE_RIGHT, SDL_SCANCODE_D };
		attackK = { SDL_SCANCODE_SPACE };
	}
	
	actionMapping->BindAction(moveUp,
		{ std::make_pair(Inputs::dPadUp, InputType::buttonPressed) }, upK);
	actionMapping->BindAction(moveDown,
		{ std::make_pair(Inputs::dPadDown, InputType::buttonPressed) }, downK);
	actionMapping->BindAction(moveLeft,
		{ std::make_pair(Inputs::dPadLeft, InputType::buttonPressed) }, leftK);
	actionMapping->BindAction(moveRight,
		{ std::make_pair(Inputs::dPadRight, InputType::buttonPressed) }, rightK);
	actionMapping->BindAction(attack,
		{ std::make_pair(Inputs::buttonEast, InputType::buttonReleased) }, attackK);

	auto controller{ std::make_unique<Controller>() };
	controller->StoreInputMapping(actionMapping);
	controller->BindToControllerDevice(controllerIdx);

	InputManager::GetInstance().AddController(controller);
}

void FH::DiggerApp::LoadTextures()
{
	auto& resourceManager{ ResourceManager::GetInstance() };

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
	resourceManager.LoadTexture("Grave/GRAVE1.png", "Grave1");
	resourceManager.LoadTexture("Grave/GRAVE2.png", "Grave2");
	resourceManager.LoadTexture("Grave/GRAVE3.png", "Grave3");
	resourceManager.LoadTexture("Grave/GRAVE4.png", "Grave4");
	resourceManager.LoadTexture("Grave/GRAVE5.png", "Grave5");
	/////////////////////
	
	/////////////////////////
	// Projectile Textures //
	resourceManager.LoadTexture("Projectile/FIRE1.png", "Fire1");
	resourceManager.LoadTexture("Projectile/FIRE2.png", "Fire2");
	resourceManager.LoadTexture("Projectile/FIRE3.png", "Fire3");
	/////////////////////////


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

	/////////////////
	// UI TEXTURES //
	resourceManager.LoadTexture("Numbers/NUM0.png", "0");
	resourceManager.LoadTexture("Numbers/NUM1.png", "1");
	resourceManager.LoadTexture("Numbers/NUM2.png", "2");
	resourceManager.LoadTexture("Numbers/NUM3.png", "3");
	resourceManager.LoadTexture("Numbers/NUM4.png", "4");
	resourceManager.LoadTexture("Numbers/NUM5.png", "5");
	resourceManager.LoadTexture("Numbers/NUM6.png", "6");
	resourceManager.LoadTexture("Numbers/NUM7.png", "7");
	resourceManager.LoadTexture("Numbers/NUM8.png", "8");
	resourceManager.LoadTexture("Numbers/NUM9.png", "9");
	/////////////////
}

void FH::DiggerApp::LoadSounds()
{
	SoundLocator::RegisterSystem(std::make_unique<SoundSystem>());

	auto& service{ SoundLocator::GetSoundService() };

	const std::string data{ "../Data/" };

	service.LoadSong("MainBGM", data + "Songs/Popcorn.mp3");
	service.LoadSong("DeathBGM", data + "Songs/Death.mp3");

	service.LoadSound("PlayerDied", data + "Sounds/PlayerDied.ogg");

	service.LoadSound("BagWiggle", data + "Sounds/BagWiggle.ogg");
	service.LoadSound("BagBreak", data + "Sounds/BagBreak.ogg");
	service.LoadSound("BagFall", data + "Sounds/BagFall.ogg");
	service.LoadSound("CoinGrab", data + "Sounds/CoinGrab.ogg");

	service.LoadSound("GemGrabBase", data + "Sounds/GemGrabBase.ogg");
	service.LoadSound("GemGrab1", data + "Sounds/GemGrab1.ogg");
	service.LoadSound("GemGrab2", data + "Sounds/GemGrab2.ogg");
	service.LoadSound("GemGrab3", data + "Sounds/GemGrab3.ogg");
	service.LoadSound("GemGrab4", data + "Sounds/GemGrab4.ogg");
	service.LoadSound("GemGrab5", data + "Sounds/GemGrab5.ogg");
	service.LoadSound("GemGrab6", data + "Sounds/GemGrab6.ogg");
	service.LoadSound("GemGrab7", data + "Sounds/GemGrab7.ogg");
	service.LoadSound("GemGrab8", data + "Sounds/GemGrab8.ogg");

	service.LoadSound("BallShot", data + "Sounds/BallShot.ogg");
	service.LoadSound("BallBreak", data + "Sounds/BallBreak.ogg");
}
