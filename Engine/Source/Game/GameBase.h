#pragma once

#include "Memory/ArenaAllocator.h"

namespace Micro
{
class GameObject;

class GameBase
{
public:
    explicit GameBase(ArenaAllocator& persistentArena) : m_persistentArena(persistentArena) {}
    virtual ~GameBase() = default;

    GameBase(const GameBase&) = delete;
    GameBase& operator=(const GameBase&) = delete;
    GameBase(GameBase&&) = delete;
    GameBase& operator=(GameBase&&) = delete;

    void Init();
    void Resize(int screenWidth, int screenHeight);

    virtual void OnInit() = 0;
    virtual void Update(ArenaAllocator& frameArena, float deltaTime) = 0;
    virtual void Render() = 0;

    void UpdateGameObjects(float deltaTime);
    void Render3DGameObjects();
    void Render2DGameObjects();

    template <typename T, typename... Args>
    T* CreateGameObject(Args&&... args)
    {
        T* gameObject = m_persistentArena.Allocate<T>(m_persistentArena, std::forward<Args>(args)...);
        if (gameObject != nullptr)
        {
            m_gameObjects.push_back(gameObject);
        }
        return gameObject;
    }

    std::string GetWindowTitle() const { return m_windowTitle; }
    bool ShouldClose() const { return m_shouldClose; }

protected:
    ArenaAllocator& m_persistentArena;
    std::string m_windowTitle;

    float m_screenWidth = 0;
    float m_screenHeight = 0;

    bool m_shouldClose = false;

    std::vector<GameObject*> m_gameObjects;
};
}  // namespace Micro
