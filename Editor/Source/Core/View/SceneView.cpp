#include "SceneView.h"
#include "Core/Log.h"

namespace Micro
{
    SceneView::~SceneView()
    {
        Log::Get().SetLogCallback(nullptr);
    }

    void SceneView::Init(int width, int height)
    {
        m_Width = width;
        m_Height = height;

        m_Camera.SetPosition({0.0f, 10.0f, 10.0f});
        m_Camera.SetTarget({0.0f, 0.0f, 0.0f});
        m_Camera.SetUp({0.0f, 1.0f, 0.0f});
        m_Camera.SetFovy(60.0f);
        m_Camera.SetProjection(CAMERA_PERSPECTIVE);

        MVector3 forward = Vector3Subtract(m_Camera.target, m_Camera.position);
        forward = forward.Normalize();

        m_Yaw = atan2f(forward.x, forward.z);
        m_Pitch = asinf(forward.y);

        Log::Get().SetLogCallback([this](const LogEntry& entry) { m_SceneLogView.AddLogEntry(entry); });
    }

    void SceneView::Update()
    {
        UpdateCamera();
    }

    void SceneView::Render(ImVec2 size)
    {
        m_RenderTexture.BeginMode();
        ClearBackground(DARKGRAY);
        BeginMode3D(m_Camera);

        Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(100, 1.0f);

        EndMode3D();

        m_SceneLogView.Update();
        m_SceneLogView.Render(size);

        m_RenderTexture.EndMode();
    }

    void SceneView::Resize(int width, int height)
    {
        if (width != m_Width || height != m_Height)
        {
            m_RenderTexture.Unload();
            m_RenderTexture = LoadRenderTexture(width, height);
            m_Width = width;
            m_Height = height;
        }
    }

    void SceneView::UpdateCamera()
    {
        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f)
        {
            m_MoveSpeed *= (1.0f + wheel * 0.1f);
            m_MoveSpeed = Clamp(m_MoveSpeed, 1.0f, 100.0f);

            MICRO_LOG_INFO("Camera Move Speed: " + std::to_string(m_MoveSpeed));
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            Vector2 delta = GetMouseDelta();
            m_Yaw -= delta.x * m_MouseSensitivity;
            m_Pitch -= delta.y * m_MouseSensitivity;
            m_Pitch = Clamp(m_Pitch, -1.55f, 1.55f);  // avoid gimbal flip
        }

        Vector3 forward = {cosf(m_Pitch) * sinf(m_Yaw), sinf(m_Pitch), cosf(m_Pitch) * cosf(m_Yaw)};
        forward = Vector3Normalize(forward);
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, {0, 1, 0}));
        Vector3 up = Vector3CrossProduct(right, forward);

        float speed = m_MoveSpeed * GetFrameTime();

        if (IsKeyDown(KEY_W)) m_Camera.position = Vector3Add(m_Camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) m_Camera.position = Vector3Subtract(m_Camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_A)) m_Camera.position = Vector3Subtract(m_Camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_D)) m_Camera.position = Vector3Add(m_Camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_E)) m_Camera.position.y += speed;
        if (IsKeyDown(KEY_Q)) m_Camera.position.y -= speed;

        m_Camera.target = Vector3Add(m_Camera.position, forward);
        m_Camera.up = up;
    }

}  // namespace Micro
