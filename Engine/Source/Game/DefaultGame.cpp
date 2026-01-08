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

        m_cubeObject = GetScene()->CreateGameObject("Cube");
        auto transformMesh = m_cubeObject->AddComponent<TransformComponent>();
        transformMesh->SetLocalPosition(MVector3{0.0f, 0.5f, 0.0f});
        transformMesh->SetLocalScale(MVector3{3.0f, 3.0f, 3.0f});
        auto mesh = m_cubeObject->AddComponent<MeshComponent>();
        mesh->SetMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
        mesh->GetMaterial()->maps[MATERIAL_MAP_DIFFUSE].color = RED;

        m_imageObject = GetScene()->CreateGameObject("Image");
        auto transformImage = m_imageObject->AddComponent<TransformComponent>();
        transformImage->SetLocalPosition(MVector3{50.0f, 50.0f, 0.0f});
        auto image = m_imageObject->AddComponent<ImageComponent>();
        Image uiImg = GenImageColor(128, 128, MColor(0, 0, 255, 200));
        image->SetTexture(LoadTextureFromImage(uiImg));
        image->SetSourceRect(MRectangle{0, 0, 128, 128});
        UnloadImage(uiImg);

        m_textObject = GetScene()->CreateGameObject("Text");
        auto transformText = m_textObject->AddComponent<TransformComponent>();
        transformText->SetParent(transformImage);
        transformText->SetLocalPosition(MVector3{5.0f, 5.0f, 0.0f});
        auto text = m_textObject->AddComponent<TextComponent>();
        text->SetText("Hello World");
    }

    void DefaultGame::OnUpdate(float deltaTime)
    {
        m_time += deltaTime;

        if (m_cubeObject != nullptr)
        {
            auto transform = m_cubeObject->GetComponent<TransformComponent>();
            MQuaternion rotation = transform->GetLocalRotation();
            MQuaternion deltaRotation = MQuaternion::FromEuler(MVector3{0.0f, 1.0f * deltaTime, 0.0f});
            MQuaternion newRotation = rotation * deltaRotation;
            transform->SetLocalRotation(newRotation);
        }

        if (m_imageObject != nullptr)
        {
            static const MVector3 initialImagePos = m_imageObject->GetComponent<TransformComponent>()->GetLocalPosition();
            auto transform = m_imageObject->GetComponent<TransformComponent>();
            MVector3 position = transform->GetLocalPosition();
            position.y = initialImagePos.y + sin(m_time * 2.0f) * 20.0f;
            transform->SetLocalPosition(position);
        }
    }

    void DefaultGame::OnShutdown() {}
}  // namespace Micro