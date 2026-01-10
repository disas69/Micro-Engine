#pragma once

namespace Micro
{
    class Scene;

    class SceneSaver
    {
    public:
        static void Save(const Scene* scene, const std::string& path);
    };

}  // namespace Micro