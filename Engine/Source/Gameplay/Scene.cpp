#include "Scene.h"
#include "Systems/TransformSystem.h"

namespace Micro
{
    GameObject* Scene::CreateGameObject(const std::string& name)
    {
        // ReSharper disable once CppDFALocalValueEscapesFunction
        return CreateGameObject(name, GUID());
    }

    GameObject* Scene::CreateGameObject(const std::string& name, GUID guid)
    {
        auto newGameObject = std::make_unique<GameObject>(name, guid);

        GameObject* rawPtr = newGameObject.get();
        m_GameObjects.push_back(std::move(newGameObject));

        // ReSharper disable once CppDFALocalValueEscapesFunction
        return rawPtr;
    }

    GameObject* Scene::FindGameObjectByName(const std::string& name) const
    {
        for (auto& gameObject : m_GameObjects)
        {
            if (gameObject->GetName() == name)
            {
                return gameObject.get();
            }
        }

        return nullptr;
    }

    GameObject* Scene::FindGameObjectByGUID(GUID guid) const
    {
        for (auto& gameObject : m_GameObjects)
        {
            if (gameObject->GetGUID() == guid)
            {
                return gameObject.get();
            }
        }

        return nullptr;
    }

    void Scene::Update(float deltaTime)
    {
        for (auto& gameObject : m_GameObjects)
        {
            if (!gameObject->IsActive())
            {
                continue;
            }

            for (const auto component : gameObject->GetAllComponents())
            {
                if (component->IsEnabled())
                {
                    component->OnUpdate(deltaTime);
                }
            }
        }
    }

    void Scene::LateUpdate(float deltaTime)
    {
        for (auto& gameObject : m_GameObjects)
        {
            if (!gameObject->IsActive())
            {
                continue;
            }

            for (const auto component : gameObject->GetAllComponents())
            {
                if (component->IsEnabled())
                {
                    component->OnLateUpdate(deltaTime);
                }
            }
        }

        for (auto& gameObject : m_GameObjects)
        {
            gameObject->RemoveDestroyedComponents();
        }

        RemoveDestroyedGameObjects();
    }

    void Scene::Destroy() const
    {
        for (auto& gameObject : m_GameObjects)
        {
            gameObject->Destroy();
        }
    }

    void Scene::RemoveDestroyedGameObjects()
    {
        m_GameObjects.erase(std::remove_if(m_GameObjects.begin(), m_GameObjects.end(), [](const std::unique_ptr<GameObject>& obj)
        {
            return obj->IsDestroyed();
        }),
        m_GameObjects.end());
    }
}  // namespace Micro