#include "DefaultGame.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Components/ImageComponent.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/TextComponent.h"

namespace Micro
{
    DefaultGame::DefaultGame()
    {
        m_windowTitle = "Default Game";
    }

    void DefaultGame::OnInit()
    {
        GameObject* cameraObject = GetScene()->CreateGameObject("Camera");
        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetPosition(MVector3{5.0f, 5.0f, 5.0f});
        camera->SetTarget(MVector3{0.0f, 1.0f, 0.0f});

        SetMainCamera(camera->GetCamera());

        GameObject* cubeObject = GetScene()->CreateGameObject("Cube");
        auto transformMesh = cubeObject->AddComponent<TransformComponent>();
        transformMesh->SetLocalPosition(MVector3{0.0f, 0.5f, 0.0f});
        transformMesh->SetLocalScale(MVector3{3.0f, 3.0f, 3.0f});
        auto mesh = cubeObject->AddComponent<MeshComponent>();
        mesh->SetMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
        mesh->GetMaterial()->maps[MATERIAL_MAP_DIFFUSE].color = RED;
        m_cubeObject = cubeObject;

        GameObject* imageObject = GetScene()->CreateGameObject("Image");
        auto transformImage = imageObject->AddComponent<TransformComponent>();
        transformImage->SetLocalPosition(MVector3{50.0f, 50.0f, 0.0f});
        auto image = imageObject->AddComponent<ImageComponent>();
        Image uiImg = GenImageColor(128, 128, MColor(0, 0, 255, 200));
        image->SetTexture(LoadTextureFromImage(uiImg));
        image->SetSourceRect(MRectangle{0, 0, 128, 128});
        UnloadImage(uiImg);

        GameObject* textObject = GetScene()->CreateGameObject("Text");
        auto transformText = textObject->AddComponent<TransformComponent>();
        transformText->SetLocalPosition(MVector3{55.0f, 55.0f, 0.0f});
        auto text = textObject->AddComponent<TextComponent>();
        text->SetText("Hello World");
    }

    void DefaultGame::OnUpdate(float deltaTime)
    {
        if (m_cubeObject != nullptr)
        {
            auto transform = m_cubeObject->GetComponent<TransformComponent>();
            MQuaternion rotation = transform->GetLocalRotation();
            MQuaternion deltaRotation = MQuaternion::FromEuler(MVector3{0.0f, 1.0f * deltaTime, 0.0f});
            MQuaternion newRotation = rotation * deltaRotation;
            transform->SetLocalRotation(newRotation);
        }
    }

    void DefaultGame::OnShutdown() {}
}  // namespace Micro