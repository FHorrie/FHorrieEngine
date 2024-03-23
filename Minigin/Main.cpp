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
#include "CacheTestComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "Action.h"
#include "Command.h"
#include "InputMapping.h"
#include "BaseInputDevice.h"
#include "Controller.h"

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
	backgroundObj->AddComponent(std::make_unique<FH::TextureComponent>(backgroundObj.get(), "logo.tga", 216.f, 180.f));

	auto textObj = std::make_unique<FH::GameObject>();
	textObj->AddComponent(std::make_unique<FH::TextComponent>(textObj.get(), "Programming 4 Assignment", 150.f, 50.f));

	auto fpsObj = std::make_unique<FH::GameObject>();
	fpsObj->AddComponent(std::make_unique<FH::FPSCounter>(fpsObj.get()));

	//Sequence of addition defines depth value (WIP)
	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(textObj));
	scene.Add(std::move(fpsObj));
}

void AddPlayerInput(FH::Scene& scene)
{
	auto pacManObj{ std::make_unique<FH::GameObject>() };
	pacManObj->SetLocalPosition(glm::vec3(100.f, 100.f, 0.f));
	pacManObj->AddComponent(std::make_unique<FH::TextureComponent>(pacManObj.get(), "pacman.png"));

	auto pacRedObj{ std::make_unique<FH::GameObject>() };
	pacRedObj->SetLocalPosition(glm::vec3(150.f, 100.f, 0.f));
	pacRedObj->AddComponent(std::make_unique<FH::TextureComponent>(pacRedObj.get(), "pacred.png"));

	auto moveUpController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacManObj.get(), glm::vec3(0.f, -1.f, 0.f), 200.f)) };
	auto moveDownController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacManObj.get(), glm::vec3(0.f, 1.f, 0.f), 200.f)) };
	auto moveLeftController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacManObj.get(), glm::vec3(-1.f, 0.f, 0.f), 200.f)) };
	auto moveRightController{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacManObj.get(), glm::vec3(1.f, 0.f, 0.f), 200.f)) };

	auto moveUpKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacRedObj.get(), glm::vec3(0.f, -1.f, 0.f), 400.f)) };
	auto moveDownKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacRedObj.get(), glm::vec3(0.f, 1.f, 0.f), 400.f)) };
	auto moveLeftKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacRedObj.get(), glm::vec3(-1.f, 0.f, 0.f), 400.f)) };
	auto moveRightKeyboard{ std::make_unique<FH::Action>(std::make_unique<FH::MoveCommand>(pacRedObj.get(), glm::vec3(1.f, 0.f, 0.f), 400.f)) };

	auto controllerActionMapping{ std::make_unique<FH::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, { std::make_pair(FH::Inputs::dPadUp,FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveDownController, { std::make_pair(FH::Inputs::dPadDown,FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveLeftController, { std::make_pair(FH::Inputs::dPadLeft,FH::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveRightController, { std::make_pair(FH::Inputs::dPadRight,FH::InputType::buttonPressed) }, {});

	auto keyboardActionMapping{ std::make_unique<FH::InputMapping>() };
	keyboardActionMapping->BindAction(moveUpKeyboard, {}, { SDL_SCANCODE_W });
	keyboardActionMapping->BindAction(moveDownKeyboard, {}, { SDL_SCANCODE_S });
	keyboardActionMapping->BindAction(moveLeftKeyboard, {}, { SDL_SCANCODE_A });
	keyboardActionMapping->BindAction(moveRightKeyboard, {}, { SDL_SCANCODE_D });

	auto controller{ std::make_unique<FH::Controller>() };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	auto keyboard{ std::make_unique<FH::Controller>() };
	keyboard->StoreInputMapping(keyboardActionMapping);

	FH::InputManager::GetInstance().AddController(controller);
	FH::InputManager::GetInstance().AddController(keyboard);

	scene.Add(std::move(pacManObj));
	scene.Add(std::move(pacRedObj));
}

int main(int, char*[]) {
	srand(int(time(nullptr)));
	FH::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}