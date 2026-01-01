#include "DefaultGame.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Transform2DComponent.h"
#include "Gameplay/SpriteComponent.h"
#include "Gameplay/TransformComponent.h"
#include "Gameplay/MeshComponent.h"

using namespace Micro;

DefaultGame::DefaultGame(ArenaAllocator& persistentArena) : GameBase(persistentArena)
{
    m_windowTitle = "Default Game";
}

void DefaultGame::OnInit()
{
    // Setup 3D camera
    m_camera.position = raylib::Vector3{5.0f, 5.0f, 5.0f};
    m_camera.target = raylib::Vector3{0.0f, 1.0f, 0.0f};
    m_camera.up = raylib::Vector3{0.0f, 1.0f, 0.0f};
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;

    // 2D GameObject example
    m_2dGameObject = CreateGameObject<GameObject>(std::string("SpriteGameObject"));
    auto transform2d = m_2dGameObject->AddComponent<Transform2DComponent>();
    transform2d->Position = raylib::Vector2{m_screenWidth / 2.0f, m_screenHeight / 2.0f};
    auto sprite = m_2dGameObject->AddComponent<SpriteComponent>();
    sprite->SourceRect = raylib::Rectangle{0, 0, 100, 100};
    sprite->Tint = BLUE;

    // 3D GameObject example
    m_3dGameObject = CreateGameObject<GameObject>(std::string("CubeGameObject"));
    auto transform3d = m_3dGameObject->AddComponent<TransformComponent>();
    transform3d->Position = raylib::Vector3{0.0f, 1.0f, 0.0f};
    transform3d->Scale = raylib::Vector3{1.0f, 1.0f, 1.0f};

    auto staticMesh = m_3dGameObject->AddComponent<MeshComponent>();
    staticMesh->ObjectMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    staticMesh->ObjectMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;
}

void DefaultGame::Update(ArenaAllocator& frameArena, float deltaTime)
{
    UpdateGameObjects(deltaTime);

    // Update 2D object
    auto transform2d = m_2dGameObject->GetComponent<Transform2DComponent>();
    // currentPosition.y = m_screenHeight / 2.0f + 100.0f * sinf(GetTime() * 2.0f);
    transform2d->Scale = raylib::Vector2{1.0f + 1.0f * sinf(GetTime() * 3.0f), 1.0f + 1.0f * sinf(GetTime() * 3.0f)};
    transform2d->Rotation = fmodf(transform2d->Rotation + 90.0f * deltaTime, 360.0f);

    // Update 3D object
    auto transform3d = m_3dGameObject->GetComponent<TransformComponent>();
    transform3d->Rotation.y = fmodf(transform3d->Rotation.y + 50.0f * deltaTime, 360.0f);  // Rotate around Y-axis
}

void DefaultGame::Render()
{
    BeginMode3D(m_camera);
    Render3DGameObjects();
    EndMode3D();

    Render2DGameObjects();

    // Draw 2D text
    int textWidth = MeasureText("Default game is running!", 20);
    DrawText("Default game is running!", m_screenWidth / 2.0f - textWidth / 2.0f, m_screenHeight / 2.0f - 10, 20, LIGHTGRAY);
}