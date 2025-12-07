#pragma once

#include <Camera3D.hpp>
#include <RenderTexture.hpp>

namespace Micro
{
class SceneView
{
public:
    SceneView() = default;
    SceneView(int width, int height);

    void Render();
    void Resize(int width, int height);

    raylib::RenderTexture* GetRenderTexture()
    {
        return &m_renderTexture;
    }

private:
    int m_width;
    int m_height;

    raylib::RenderTexture m_renderTexture;
    raylib::Camera m_camera;
};
}

