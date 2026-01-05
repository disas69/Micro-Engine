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

        MRenderTexture* GetRenderTexture() { return &m_renderTexture; }

    private:
        int m_width;
        int m_height;

        MRenderTexture m_renderTexture;
        MCamera3D m_camera;
        SceneLogView m_sceneLogView;

        float m_moveSpeed = 10.0f;
        float m_mouseSensitivity = 0.007f;
        float m_yaw = 0.0f;
        float m_pitch = 0.0f;

        void UpdateCamera();
    };
}  // namespace Micro
