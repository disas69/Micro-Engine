#pragma once

namespace Micro
{
    class Scene;

    class RenderSystem
    {
    public:
        static void Render(MCamera3D* camera, Scene* scene);
    };
}  // namespace Micro