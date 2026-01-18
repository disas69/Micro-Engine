#pragma once

namespace Micro
{
    class Scene;
    class TransformComponent;

    class TransformSystem
    {
    public:
        static void Update(Scene* scene);

    private:
        static void UpdateRecursive(TransformComponent* transform, const MMatrix& parentWorldMatrix);
    };
}  // namespace Micro