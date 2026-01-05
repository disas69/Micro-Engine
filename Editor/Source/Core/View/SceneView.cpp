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
        m_width = width;
        m_height = height;

        m_camera.SetPosition({0.0f, 10.0f, 10.0f});
        m_camera.SetTarget({0.0f, 0.0f, 0.0f});
        m_camera.SetUp({0.0f, 1.0f, 0.0f});
        m_camera.SetFovy(60.0f);
        m_camera.SetProjection(CAMERA_PERSPECTIVE);

        MVector3 forward = Vector3Subtract(m_camera.target, m_camera.position);
        forward = forward.Normalize();

        m_yaw = atan2f(forward.x, forward.z);
        m_pitch = asinf(forward.y);

        Log::Get().SetLogCallback([this](const LogEntry& entry) { m_sceneLogView.AddLogEntry(entry); });
    }

    void SceneView::Update()
    {
        UpdateCamera();
    }

    void SceneView::Render(ImVec2 size)
    {
        m_renderTexture.BeginMode();
        ClearBackground(DARKGRAY);
        BeginMode3D(m_camera);

        Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(100, 1.0f);

        EndMode3D();

        m_sceneLogView.Update();
        m_sceneLogView.Render(size);

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

    void SceneView::UpdateCamera()
    {
        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f)
        {
            m_moveSpeed *= (1.0f + wheel * 0.1f);
            m_moveSpeed = Clamp(m_moveSpeed, 1.0f, 100.0f);

            MICRO_LOG_INFO("Camera Move Speed: " + std::to_string(m_moveSpeed));
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            Vector2 delta = GetMouseDelta();
            m_yaw -= delta.x * m_mouseSensitivity;
            m_pitch -= delta.y * m_mouseSensitivity;
            m_pitch = Clamp(m_pitch, -1.55f, 1.55f);  // avoid gimbal flip
        }

        Vector3 forward = {cosf(m_pitch) * sinf(m_yaw), sinf(m_pitch), cosf(m_pitch) * cosf(m_yaw)};
        forward = Vector3Normalize(forward);
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, {0, 1, 0}));
        Vector3 up = Vector3CrossProduct(right, forward);

        float speed = m_moveSpeed * GetFrameTime();

        if (IsKeyDown(KEY_W)) m_camera.position = Vector3Add(m_camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) m_camera.position = Vector3Subtract(m_camera.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_A)) m_camera.position = Vector3Subtract(m_camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_D)) m_camera.position = Vector3Add(m_camera.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_E)) m_camera.position.y += speed;
        if (IsKeyDown(KEY_Q)) m_camera.position.y -= speed;

        m_camera.target = Vector3Add(m_camera.position, forward);
        m_camera.up = up;
    }

}  // namespace Micro
