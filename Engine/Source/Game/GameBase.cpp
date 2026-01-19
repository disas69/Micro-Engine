#include "GameBase.h"

#include "Gameplay/Components/CameraComponent.h"
#include "Services/SceneService.h"
#include "Services/ServiceLocator.h"

namespace Micro
{
    void GameBase::RegisterCustomServices()
    {
        // Override to register custom services
    }

    void GameBase::RegisterCustomComponents()
    {
        // Override to register custom components
    }

    void GameBase::RegisterCustomSystems()
    {
        // Override to register custom systems
    }

    void GameBase::LoadStartupScene()
    {
        ServiceLocator::Get<SceneService>()->LoadStartupScene();
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
        return ServiceLocator::Get<SceneService>()->GetActiveScene();
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

    void GameBase::LateUpdate(float deltaTime)
    {
        if (Scene* scene = GetScene())
        {
            scene->LateUpdate(deltaTime);
        }

        OnLateUpdate(deltaTime);
    }

    void GameBase::Shutdown()
    {
        ServiceLocator::Get<SceneService>()->UnloadScene();
        OnShutdown();
    }
}  // namespace Micro