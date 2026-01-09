#pragma once

namespace Micro
{
    class Scene;

    class SceneLoader
    {
    public:
        static std::unique_ptr<Scene> Load(const std::string& path);
    };

}  // namespace Micro