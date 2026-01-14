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
        rawPtr->OnDestroy = [this, guid]() { OnGameObjectDestroyed(guid); };
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

    void Scene::OnGameObjectDestroyed(GUID guid)
    {
        m_GameObjects.erase(
            std::remove_if(m_GameObjects.begin(), m_GameObjects.end(), [guid](const std::unique_ptr<GameObject>& obj) { return obj->GetGUID() == guid; }),
            m_GameObjects.end());
    }

    void Scene::Update(float deltaTime)
    {
        TransformSystem::Update(this);

        for (auto& gameObject : m_GameObjects)
        {
            for (const auto component : gameObject->GetAllComponents())
            {
                if (component->IsEnabled())
                {
                    component->OnUpdate(deltaTime);
                }
            }
        }

        for (auto& gameObject : m_GameObjects)
        {
            gameObject->RemoveDestroyedComponents();
        }
    }

    void Scene::DestroyAll()
    {
        for (auto& gameObject : m_GameObjects)
        {
            gameObject->DestroyInternal();
        }

        m_GameObjects.clear();
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
}  // namespace Micro