#pragma once

#include "SceneLogView.h"
#include "imgui.h"

#include <Camera3D.hpp>
#include <RenderTexture.hpp>

namespace Micro
{
    class SceneView
    {
    public:
        SceneView() = default;
        ~SceneView();

        SceneView(const SceneView&) = delete;
        SceneView& operator=(const SceneView&) = delete;
        SceneView(SceneView&&) = delete;
        SceneView& operator=(SceneView&&) = delete;

        void Init(int width, int height);
        void Update();
        void Render(ImVec2 size);
        void Resize(int width, int height);

        MRenderTexture* GetRenderTexture() { return &m_RenderTexture; }

    private:
        int m_Width;
        int m_Height;

        MRenderTexture m_RenderTexture;
        MCamera3D m_Camera;
        SceneLogView m_SceneLogView;

        float m_MoveSpeed = 10.0f;
        float m_MouseSensitivity = 0.007f;
        float m_Yaw = 0.0f;
        float m_Pitch = 0.0f;

        void UpdateCamera();
    };
}  // namespace Micro
