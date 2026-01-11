#pragma once

namespace Micro
{
    class Scene;

    class SceneLoader
    {
    public:
        static void Load(const std::string& path, Scene* scene);
    };

}  // namespace Micro