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
        m_gameObjects.push_back(std::move(newGameObject));
        // ReSharper disable once CppDFALocalValueEscapesFunction
        return rawPtr;
    }

    void Scene::DestroyGameObject(GUID guid)
    {
        m_gameObjects.erase(
            std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [guid](const std::unique_ptr<GameObject>& obj) { return obj->GetGUID() == guid; }),
            m_gameObjects.end());
    }

    void Scene::Update(float deltaTime)
    {
        TransformSystem::Update(this);

        for (auto& gameObject : m_gameObjects)
        {
            for (const auto& component : gameObject->GetComponents())
            {
                component->OnUpdate(deltaTime);
            }
        }
    }
}  // namespace Micro