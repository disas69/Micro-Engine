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

        virtual void RegisterCustomComponents();

        void Init(MVector2 screenSize);
        void Update(float deltaTime);
        void LateUpdate(float deltaTime);
        void Shutdown();

        Scene* GetScene();

        void SetScreenSize(MVector2 screenSize) { m_ScreenSize = screenSize; }
        MVector2 GetScreenSize() { return m_ScreenSize; }

        std::string GetWindowTitle() const { return m_WindowTitle; }
        bool ShouldClose() const { return m_ShouldClose; }

        MCamera3D* GetMainCamera() const { return m_MainCamera; }
        void SetMainCamera(MCamera3D* camera) { m_MainCamera = camera; }

    protected:
        std::string m_WindowTitle;
        MVector2 m_ScreenSize;
        bool m_ShouldClose = false;

        virtual void OnInit() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnLateUpdate(float deltaTime) {}
        virtual void OnShutdown() {}

    private:
        MCamera3D* m_MainCamera = nullptr;

        void LoadStartupScene();
        void FindMainCamera();
    };
}  // namespace Micro
