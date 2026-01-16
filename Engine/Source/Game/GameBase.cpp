#include "GameBase.h"

#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Managers/SceneManager.h"

namespace Micro
{
    void GameBase::RegisterCustomComponents()
    {
        // Override to register custom components
        // TypeRegistry::Register(&CustomComponent::GetType());
    }

    void GameBase::LoadStartupScene()
    {
        SceneManager::GetInstance().LoadStartupScene();
    }

    void GameBase::FindMainCamera()
    {
        auto camera = GetScene()->FindComponentByType<CameraComponent>();
        if (camera != nullptr)
        {
            SetMainCamera(camera->GetCamera());
        }
        else
        {
            GameObject* cameraObject = GetScene()->CreateGameObject("DefaultCamera");
            SetMainCamera(cameraObject->AddComponent<CameraComponent>()->GetCamera());
        }
    }

    Scene* GameBase::GetScene()
    {
        return SceneManager::GetInstance().GetActiveScene();
    }

    void GameBase::Init(MVector2 screenSize)
    {
        SetScreenSize(screenSize);
        LoadStartupScene();
        FindMainCamera();
        OnInit();
    }

    void GameBase::Update(float deltaTime)
    {
        if (Scene* scene = GetScene())
        {
            scene->Update(deltaTime);
        }

        OnUpdate(deltaTime);
    }

    void GameBase::Shutdown()
    {
        SceneManager::GetInstance().UnloadScene();
        OnShutdown();
    }
}  // namespace Micro