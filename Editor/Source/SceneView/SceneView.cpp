#include "SceneView.h"

using namespace Micro;

SceneView::SceneView(int width, int height) : m_width(width), m_height(height), m_renderTexture()
{
    m_camera.SetPosition({0.0f, 10.0f, 10.0f});
    m_camera.SetTarget({0.0f, 0.0f, 0.0f});
    m_camera.SetUp({0.0f, 1.0f, 0.0f});
    m_camera.SetFovy(60.0f);
    m_camera.SetProjection(CAMERA_PERSPECTIVE);
}

void SceneView::Render()
{
    UpdateCamera(&m_camera, CAMERA_ORBITAL);

    m_renderTexture.BeginMode();
    ClearBackground(DARKGRAY);
    BeginMode3D(m_camera);

    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
    DrawGrid(10, 1.0f);

    EndMode3D();
    m_renderTexture.EndMode();
}

void SceneView::Resize(int width, int height)
{
    if (width != m_width || height != m_height)
    {
        m_renderTexture.Unload();
        m_renderTexture = LoadRenderTexture(width, height);
        m_width = width;
        m_height = height;
    }
}
