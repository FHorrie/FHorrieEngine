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

void LoadBackground(dae::Scene& scene);

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	LoadBackground(scene);

	auto pacManObj{ std::make_unique<dae::GameObject>() };
	pacManObj->SetLocalPosition(glm::vec3(100.f, 100.f, 0.f));
	pacManObj->AddComponent(std::make_unique<dae::TransformComponent>(pacManObj.get(), 100.f));
	pacManObj->AddComponent(std::make_unique<dae::TextureComponent>(pacManObj.get(), "pacman.png"));

	auto PacRedObj{ std::make_unique<dae::GameObject>() };
	PacRedObj->SetLocalPosition(glm::vec3(150.f, 100.f, 0.f));
	PacRedObj->AddComponent(std::make_unique<dae::TransformComponent>(PacRedObj.get(), 200.f));
	PacRedObj->AddComponent(std::make_unique<dae::TextureComponent>(PacRedObj.get(), "pacred.png"));

	auto moveUpController{ std::make_unique<dae::Action>(std::make_unique<dae::MoveUp>()) };
	auto moveDownController{ std::make_unique<dae::Action>(std::make_unique<dae::MoveDown>()) };
	auto moveLeftController{ std::make_unique<dae::Action>(std::make_unique<dae::MoveLeft>()) };
	auto moveRightController{ std::make_unique<dae::Action>(std::make_unique<dae::MoveRight>()) };

	auto moveUpKeyboard{ std::make_unique<dae::Action>(std::make_unique<dae::MoveUp>()) };
	auto moveDownKeyboard{ std::make_unique<dae::Action>(std::make_unique<dae::MoveDown>()) };
	auto moveLeftKeyboard{ std::make_unique<dae::Action>(std::make_unique<dae::MoveLeft>()) };
	auto moveRightKeyboard{ std::make_unique<dae::Action>(std::make_unique<dae::MoveRight>()) };

	auto controllerActionMapping{ std::make_unique<dae::InputMapping>() };
	controllerActionMapping->BindAction(moveUpController, { std::make_pair(dae::Inputs::dPadUp,dae::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveDownController, { std::make_pair(dae::Inputs::dPadDown,dae::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveLeftController, { std::make_pair(dae::Inputs::dPadLeft,dae::InputType::buttonPressed) }, {});
	controllerActionMapping->BindAction(moveRightController, { std::make_pair(dae::Inputs::dPadRight,dae::InputType::buttonPressed) }, {});

	auto keyboardActionMapping{ std::make_unique<dae::InputMapping>() };
	keyboardActionMapping->BindAction(moveUpKeyboard, {}, { SDL_SCANCODE_W });
	keyboardActionMapping->BindAction(moveDownKeyboard, {}, { SDL_SCANCODE_S });
	keyboardActionMapping->BindAction(moveLeftKeyboard, {}, { SDL_SCANCODE_A });
	keyboardActionMapping->BindAction(moveRightKeyboard, {}, { SDL_SCANCODE_D });

	auto controller{ std::make_unique<dae::Controller>(pacManObj.get()) };
	controller->StoreInputMapping(controllerActionMapping);
	controller->BindToControllerDevice(0);

	auto keyboard{ std::make_unique<dae::Controller>(PacRedObj.get()) };
	keyboard->StoreInputMapping(keyboardActionMapping);

	dae::InputManager::GetInstance().AddController(controller);
	dae::InputManager::GetInstance().AddController(keyboard);

	scene.Add(std::move(pacManObj));
	scene.Add(std::move(PacRedObj));
	
	//////
	//OLD
	//auto GUIObj = std::make_unique<dae::GameObject>();
	//GUIObj->AddComponent(std::make_unique<dae::CacheTestComponent>(GUIObj.get()));
	// 
	//auto posObj = std::make_unique<dae::GameObject>();
	//posObj->SetLocalPosition(glm::vec3(200.f, 350.f, 0.f));
	//
	//auto rotationObj = std::make_unique<dae::GameObject>();
	//rotationObj->AddComponent(std::make_unique<dae::RotationComponent>(rotationObj.get(), glm::vec3(100.f, 0.f, 0.f), 1.f));
	//rotationObj->AddComponent(std::make_unique<dae::TextureComponent>(rotationObj.get(), "pacman.png"));
	//
	//auto orbitObj = std::make_unique<dae::GameObject>();
	//orbitObj->AddComponent(std::make_unique<dae::RotationComponent>(orbitObj.get(), glm::vec3(0.f, 50.f, 0.f), 3.f));
	//orbitObj->AddComponent(std::make_unique<dae::TextureComponent>(orbitObj.get(), "pacman.png"));
	//
	//auto orbit1Obj = std::make_unique<dae::GameObject>();
	//orbit1Obj->AddComponent(std::make_unique<dae::RotationComponent>(orbit1Obj.get(), glm::vec3(70.f, 70.f, 0.f), -5.f));
	//orbit1Obj->AddComponent(std::make_unique<dae::TextureComponent>(orbit1Obj.get(), "pacman.png"));
	//
	//posObj->AddChild(rotationObj.get());
	//rotationObj->AddChild(orbitObj.get());
	//orbitObj->AddChild(orbit1Obj.get());
	//////
}

void LoadBackground(dae::Scene& scene)
{
	auto backgroundObj = std::make_unique<dae::GameObject>();
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj.get(), "background.tga"));
	backgroundObj->AddComponent(std::make_unique<dae::TextureComponent>(backgroundObj.get(), "logo.tga", 216.f, 180.f));

	auto textObj = std::make_unique<dae::GameObject>();
	textObj->AddComponent(std::make_unique<dae::TextComponent>(textObj.get(), "Programming 4 Assignment", 150.f, 50.f));

	auto fpsObj = std::make_unique<dae::GameObject>();
	fpsObj->AddComponent(std::make_unique<dae::FPSCounter>(fpsObj.get()));

	//Sequence of addition defines depth value (WIP)
	scene.Add(std::move(backgroundObj));
	scene.Add(std::move(textObj));
	scene.Add(std::move(fpsObj));
}

int main(int, char*[]) {
	srand(int(time(nullptr)));
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}