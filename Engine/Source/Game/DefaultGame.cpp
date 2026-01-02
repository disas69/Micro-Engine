#include "DefaultGame.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Transform2DComponent.h"
#include "Gameplay/SpriteComponent.h"
#include "Gameplay/TransformComponent.h"
#include "Gameplay/MeshComponent.h"
#include "Gameplay/TextComponent.h"

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
    auto mesh = m_3dGameObject->AddComponent<MeshComponent>();
    mesh->ObjectMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    mesh->ObjectMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    // Text GameObject example
    m_textGameObject = CreateGameObject<GameObject>(std::string("TextGameObject"));
    auto textTransform = m_textGameObject->AddComponent<Transform2DComponent>();
    textTransform->Position = raylib::Vector2{m_screenWidth / 2.0f - 100.0f, m_screenHeight / 2.0f - 10};
    auto text = m_textGameObject->AddComponent<TextComponent>();
    text->Text = "Default game is running!";
    text->FontSize = 20;
    text->Color = LIGHTGRAY;
}

void DefaultGame::OnUpdate(ArenaAllocator& frameArena, float deltaTime)
{
    UpdateGameObjects(deltaTime);

    // Update 2D object
    auto transform2d = m_2dGameObject->GetComponent<Transform2DComponent>();
    // currentPosition.y = m_screenHeight / 2.0f + 100.0f * sinf(GetTime() * 2.0f);
    transform2d->Scale = raylib::Vector2{1.0f + 1.0f * sinf(GetTime() * 3.0f), 1.0f + 1.0f * sinf(GetTime() * 3.0f)};
    transform2d->Rotation = fmodf(transform2d->Rotation + 90.0f * deltaTime, 360.0f);

    // Update 3D object
    auto transform3d = m_3dGameObject->GetComponent<TransformComponent>();
    transform3d->Rotation.y = fmodf(transform3d->Rotation.y + 50.0f * deltaTime, 360.0f);

    // Update text object
    auto textTransform = m_textGameObject->GetComponent<Transform2DComponent>();
    textTransform->Position.x = m_screenWidth / 2.0f - 100.0f + 20.0f * sinf(GetTime() * 2.0f);
}

void DefaultGame::OnRender()
{
    BeginMode3D(m_camera);
    Render3DGameObjects();
    EndMode3D();

    Render2DGameObjects();
    RenderUIGameObjects();
}