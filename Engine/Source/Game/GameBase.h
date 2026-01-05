#pragma once

#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"

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

        void Init(MVector2 screenSize);
        void Update(float deltaTime);
        void Shutdown();

        void SetScreenSize(MVector2 screenSize) { m_screenSize = screenSize; }
        MVector2 GetScreenSize() { return m_screenSize; }

        void SetScene(Scene* scene) { m_scene = scene; }
        Scene* GetScene() const { return m_scene; }

        std::string GetWindowTitle() const { return m_windowTitle; }
        bool ShouldClose() const { return m_shouldClose; }

        MCamera3D* GetMainCamera() const { return m_mainCamera; }
        void SetMainCamera(MCamera3D* camera) { m_mainCamera = camera; }

    protected:
        std::string m_windowTitle;
        MVector2 m_screenSize;
        bool m_shouldClose = false;

        virtual void OnInit() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnShutdown() = 0;

    private:
        Scene* m_scene = nullptr;
        MCamera3D* m_mainCamera = nullptr;
    };
}  // namespace Micro
