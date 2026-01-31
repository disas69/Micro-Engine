#include "DefaultGame.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Components/ImageComponent.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/PrimitiveMeshComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "Serialization/Scene/SceneSaver.h"
#include "Services/SceneService.h"
#include "Services/ServiceLocator.h"
#include "Assets/AssetReference.h"
#include "Services/AssetsService.h"

namespace Micro
{
    DefaultGame::DefaultGame()
    {
        m_WindowTitle = "Default Game";
    }

    void DefaultGame::OnInit()
    {
        // Load scene path
        auto camera = GetScene()->FindComponentByType<CameraComponent>();
        camera->GetTransform()->SetLocalPosition(MVector3{0.0f, 5.0f, 10.0f});
        camera->GetTransform()->LookAt(MVector3{0.0f, 2.0f, 0.0f});

        m_CubeObject = GetScene()->FindGameObjectByComponent<PrimitiveMeshComponent>();
        if (m_CubeObject != nullptr)
        {
            auto smallCube = GameObject::CreatePrimitive(PrimitiveShape::Cube, GREEN);
            smallCube->GetTransform()->SetLocalPosition(MVector3{0.0f, 1.0f, 0.0f});
            smallCube->GetTransform()->SetLocalScale(MVector3{0.5f, 0.5f, 0.5f});
            smallCube->GetTransform()->SetParent(m_CubeObject->GetTransform());
        }

        auto* sphere = GameObject::CreatePrimitive(PrimitiveShape::Sphere, BLUE);
        sphere->GetTransform()->SetLocalPosition(MVector3{-2.0f, 0.5f, 0.0f});

        auto* cylinder = GameObject::CreatePrimitive(PrimitiveShape::Cylinder, PURPLE);
        cylinder->GetTransform()->SetLocalPosition(MVector3{-5.0f, 1.0f, 2.0f});

        auto* cone = GameObject::CreatePrimitive(PrimitiveShape::Cone, YELLOW);
        cone->GetTransform()->SetLocalPosition(MVector3{0.0f, 1.0f, -2.0f});

        auto* torus = GameObject::CreatePrimitive(PrimitiveShape::Torus, PINK);
        torus->GetTransform()->SetLocalPosition(MVector3{0.0f, 0.5, 2.0f});

        m_ImageObject = GetScene()->FindGameObjectByName("Image");
        m_TextObject = GetScene()->FindGameObjectByName("Text");

        auto circleImage = GetScene()->CreateGameObject("Circle")->AddComponent<ImageComponent>();
        circleImage->SetTextureID(ServiceLocator::Get<AssetsService>()->GetAssetID("Assets/Texture/circle-128.png"));
        circleImage->SetSourceRect(MRectangle{0, 0, 128, 128});
        circleImage->SetColor(MColor::Red());
        circleImage->GetTransform()->SetParent(m_ImageObject->GetTransform());
        circleImage->GetTransform()->SetLocalPosition(MVector3{35.0f, 35.0f, 0.0f});
        circleImage->GetTransform()->SetLocalScale(MVector3{0.5f, 0.5f, 0.5f});

        // Save scene path
        // GameObject* cameraObject = GetScene()->CreateGameObject("Camera");
        // auto camera = cameraObject->AddComponent<CameraComponent>();
        // camera->SetPosition(MVector3{5.0f, 5.0f, 5.0f});
        // camera->SetTarget(MVector3{0.0f, 1.0f, 0.0f});
        //
        // SetMainCamera(camera->GetCamera());
        //
        // m_CubeObject = GetScene()->CreateGameObject("Cube");
        // m_CubeObject->GetTransform()->SetLocalPosition(MVector3{0.0f, 0.5f, 0.0f});
        // m_CubeObject->GetTransform()->SetLocalScale(MVector3{3.0f, 3.0f, 3.0f});
        // auto mesh = m_CubeObject->AddComponent<MeshComponent>();
        // mesh->GetMaterial()->maps[MATERIAL_MAP_DIFFUSE].color = RED;
        //
        // m_ImageObject = GetScene()->CreateGameObject("Image");
        // m_ImageObject->GetTransform()->SetLocalPosition(MVector3{50.0f, 50.0f, 0.0f});
        // auto image = m_ImageObject->AddComponent<ImageComponent>();
        // image->SetSourceRect(MRectangle{0, 0, 128, 128});
        // image->SetColor(MColor(0, 0, 255, 200));
        //
        // m_TextObject = GetScene()->CreateGameObject("Text");
        // m_TextObject->GetTransform()->SetParent(image->GetTransform());
        // m_TextObject->GetTransform()->SetLocalPosition(MVector3{5.0f, 5.0f, 0.0f});
        // auto text = m_TextObject->AddComponent<TextComponent>();
        // text->SetText("Hello Micro!");
        //
        // auto sceneService = ServiceLocator::Get<SceneService>();
        // sceneService->SaveScene();
    }

    void DefaultGame::OnUpdate(float deltaTime)
    {
        m_Time += deltaTime;

        if (m_CubeObject != nullptr)
        {
            MQuaternion rotation = m_CubeObject->GetTransform()->GetLocalRotation();
            MQuaternion deltaRotation = MQuaternion::FromEuler(MVector3{0.0f, 1.0f * deltaTime, 0.0f});
            MQuaternion newRotation = rotation * deltaRotation;
            m_CubeObject->GetTransform()->SetLocalRotation(newRotation);
        }

        if (m_ImageObject != nullptr)
        {
            static const MVector3 initialImagePos = m_ImageObject->GetTransform()->GetLocalPosition();
            MVector3 position = m_ImageObject->GetTransform()->GetLocalPosition();
            position.y = initialImagePos.y + sin(m_Time * 2.0f) * 20.0f;
            m_ImageObject->GetTransform()->SetLocalPosition(position);
        }
    }
}  // namespace Micro