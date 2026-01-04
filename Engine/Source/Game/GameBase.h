#pragma once

#include "Gameplay/GameObject.h"

namespace Micro
{
class GameBase
{
public:
    explicit GameBase() = default;
    virtual ~GameBase() = default;

    GameBase(const GameBase&) = delete;
    GameBase& operator=(const GameBase&) = delete;
    GameBase(GameBase&&) = delete;
    GameBase& operator=(GameBase&&) = delete;

    void Init();
    void Resize(int screenWidth, int screenHeight);

    virtual void OnInit() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnRender() = 0;

    void UpdateGameObjects(float deltaTime);
    void Render3DGameObjects();
    void Render2DGameObjects();
    void RenderUIGameObjects();

    template <typename T, typename... Args>
    T* CreateGameObject(Args&&... args)
    {
        static_assert(std::is_base_of_v<GameObject, T>, "T must derive from GameObject");

        auto gameObject = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = gameObject.get();

        m_gameObjects.push_back(std::move(gameObject));
        rawPtr->OnInit();

        return rawPtr;
    }

    std::string GetWindowTitle() const { return m_windowTitle; }
    bool ShouldClose() const { return m_shouldClose; }

protected:
    std::string m_windowTitle;

    float m_screenWidth = 0;
    float m_screenHeight = 0;

    bool m_shouldClose = false;

    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};
}  // namespace Micro
