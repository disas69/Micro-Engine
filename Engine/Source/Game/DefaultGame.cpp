#include "DefaultGame.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Transform2DComponent.h"
#include "Gameplay/SpriteComponent.h"

using namespace Micro;

DefaultGame::DefaultGame(ArenaAllocator& persistentArena) : GameBase(persistentArena)
{
    m_windowTitle = "Default Game";
}

void DefaultGame::OnInit()
{
    m_testGameObject = CreateGameObject<GameObject>(std::string("TestGameObject"));

    auto transform2d = m_testGameObject->AddComponent<Transform2DComponent>();
    transform2d->Position = raylib::Vector2{m_screenWidth / 2.0f, m_screenHeight / 2.0f};

    auto sprite = m_testGameObject->AddComponent<SpriteComponent>();
    sprite->SourceRect = raylib::Rectangle{0, 0, 100, 100};
    sprite->Tint = BLUE;
}

void DefaultGame::Update(ArenaAllocator& frameArena, float deltaTime)
{
    UpdateGameObjects(deltaTime);

    auto transform2d = m_testGameObject->GetComponent<Transform2DComponent>();
    auto currentPosition = transform2d->Position;
    auto currentScale = transform2d->Scale;
    auto currentRotation = transform2d->Rotation;

    // currentPosition.y = m_screenHeight / 2.0f + 100.0f * sinf(GetTime() * 2.0f);
    currentScale = raylib::Vector2{1.0f + 1.0f * sinf(GetTime() * 3.0f), 1.0f + 1.0f * sinf(GetTime() * 3.0f)};
    currentRotation = fmodf(currentRotation + 90.0f * deltaTime, 360.0f);

    transform2d->Position = currentPosition;
    transform2d->Scale = currentScale;
    transform2d->Rotation = currentRotation;
}

void DefaultGame::Render()
{
    RenderGameObjects();

    int textWidth = MeasureText("Default game is running!", 20);
    DrawText("Default game is running!", m_screenWidth / 2.0f - textWidth / 2.0f, m_screenHeight / 2.0f - 10, 20, LIGHTGRAY);
}