#include "DefaultGame.h"
#include "Core/RenderContext.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Components/SpriteComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "UI/Components/ImageComponent.h"
#include "Gameplay/Components/Transform2dComponent.h"
#include "UI/Components/ButtonComponent.h"

namespace Micro
{
DefaultGame::DefaultGame()
{
    m_windowTitle = "Default Game";
}

void DefaultGame::OnInit()
{
    // Setup 3D camera
    m_camera.position = MVector3{5.0f, 5.0f, 5.0f};
    m_camera.target = MVector3{0.0f, 1.0f, 0.0f};
    m_camera.up = MVector3{0.0f, 1.0f, 0.0f};
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;

    SetActiveCamera3D(&m_camera);

    // Sprite GameObject example
    Image spriteImg = GenImageChecked(256, 256, 32, 32, RED, GOLD);

    m_spriteGameObject = CreateGameObject<GameObject>(std::string("SpriteGameObject"));
    auto transformSprite = m_spriteGameObject->AddComponent<TransformComponent>();
    transformSprite->Position = MVector3{-2.0f, 1.0f, -1.0f};
    transformSprite->Scale = MVector3{1.0f, 2.0f, 1.0f};
    auto sprite = m_spriteGameObject->AddComponent<SpriteComponent>();
    sprite->SpriteTexture = LoadTextureFromImage(spriteImg);
    sprite->SourceRect = MRectangle{0, 0, 1, 1};
    sprite->Tint = BLUE;

    UnloadImage(spriteImg);

    // 3D GameObject example
    m_3dGameObject = CreateGameObject<GameObject>(std::string("CubeGameObject"));
    auto transform3d = m_3dGameObject->AddComponent<TransformComponent>();
    transform3d->Position = MVector3{0.0f, 1.0f, 0.0f};
    transform3d->Scale = MVector3{1.0f, 1.0f, 1.0f};
    auto mesh = m_3dGameObject->AddComponent<MeshComponent>();
    mesh->ObjectMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    mesh->ObjectMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    // Text GameObject example
    m_textGameObject = CreateGameObject<GameObject>(std::string("TextGameObject"));
    auto textTransform = m_textGameObject->AddComponent<Transform2dComponent>();
    textTransform->Position = MVector2{m_screenWidth / 2.0f - 100.0f, m_screenHeight / 2.0f - 10};
    auto text = m_textGameObject->AddComponent<TextComponent>();
    text->Text = "Default game is running!";
    text->FontSize = 20;
    text->Color = LIGHTGRAY;

    // Image GameObject example
    Image uiImg = GenImageColor(128, 128, MColor(0, 0, 255, 200));

    m_imageGameObject = CreateGameObject<GameObject>(std::string("ImageGameObject"));
    auto imageTransform = m_imageGameObject->AddComponent<Transform2dComponent>();
    imageTransform->Position = MVector2{10, 10};
    auto image = m_imageGameObject->AddComponent<ImageComponent>();
    image->Texture = LoadTextureFromImage(uiImg);
    image->SourceRect = MRectangle{0, 0, 128, 128};

    UnloadImage(uiImg);

    // Button GameObject example
    m_buttonGameObject = CreateGameObject<GameObject>(std::string("ButtonGameObject"));
    auto buttonTransform = m_buttonGameObject->AddComponent<Transform2dComponent>();
    buttonTransform->Position = MVector2{m_screenWidth / 2.0f - 50.0f, m_screenHeight - 50.0f};
    auto button = m_buttonGameObject->AddComponent<ButtonComponent>();
    button->Size = MVector2{150.0f, 50.0f};
    button->SetText("Change Cube Color");
    button->SetOnClick(
        [this]()
        {
            auto mesh = m_3dGameObject->GetComponent<MeshComponent>();
            mesh->ObjectMaterial.maps[MATERIAL_MAP_DIFFUSE].color = MColor::FromHSV(static_cast<float>(GetRandomValue(0, 360)), 0.75f, 0.9f);
        });
}

void DefaultGame::OnUpdate(float deltaTime)
{
    UpdateGameObjects(deltaTime);

    // Update sprite object
    auto transformSprite = m_spriteGameObject->GetComponent<TransformComponent>();
    transformSprite->Rotation.y = fmodf(transformSprite->Rotation.y + 10.0f * deltaTime, 360.0f);

    // Update 3D object
    auto transform3d = m_3dGameObject->GetComponent<TransformComponent>();
    transform3d->Rotation.y = fmodf(transform3d->Rotation.y + 50.0f * deltaTime, 360.0f);

    // Update text object
    auto textTransform = m_textGameObject->GetComponent<Transform2dComponent>();
    textTransform->Position.x = m_screenWidth / 2.0f - 100.0f + 20.0f * sinf(GetTime() * 2.0f);
}

void DefaultGame::OnRender()
{
    BeginMode3D(GetActiveCamera3D());
    Render3DGameObjects();
    EndMode3D();

    Render2DGameObjects();
    RenderUIGameObjects();
}
}  // namespace Micro