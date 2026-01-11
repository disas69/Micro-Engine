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
        rawPtr->OnDestroy = [this, guid]() { DestroyGameObject(guid); };

        m_GameObjects.push_back(std::move(newGameObject));
        // ReSharper disable once CppDFALocalValueEscapesFunction
        return rawPtr;
    }

    void Scene::DestroyGameObject(GUID guid)
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
                component->OnUpdate(deltaTime);
            }
        }
    }

    void Scene::Clear()
    {
        for (auto& gameObject : m_GameObjects)
        {
            gameObject->Destroy(false);
        }

        m_GameObjects.clear();
    }
}  // namespace Micro