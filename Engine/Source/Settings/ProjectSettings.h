#pragma once

#include "Settings.h"
#include "yaml-cpp/node/node.h"

namespace Micro
{
    struct ProjectSettings : Settings
    {
        uint32_t WindowWidth = 1280;
        uint32_t WindowHeight = 720;
        uint32_t TargetFPS = 60;

        std::vector<std::string> Scenes;
        uint32_t StartupSceneIndex = 0;

        std::string GetFileName() override { return "ProjectSettings.asset"; }
    };
}  // namespace Micro

namespace YAML
{
    template <>
    struct convert<Micro::ProjectSettings>
    {
        static Node encode(const Micro::ProjectSettings& rhs)
        {
            Node node;
            node["WindowWidth"] = rhs.WindowWidth;
            node["WindowHeight"] = rhs.WindowHeight;
            node["TargetFPS"] = rhs.TargetFPS;
            node["Scenes"] = rhs.Scenes;
            node["StartupSceneIndex"] = rhs.StartupSceneIndex;
            return node;
        }

        static bool decode(const Node& node, Micro::ProjectSettings& rhs)
        {
            if (!node.IsMap()) return false;
            if (node["WindowWidth"]) rhs.WindowWidth = node["WindowWidth"].as<uint32_t>();
            if (node["WindowHeight"]) rhs.WindowHeight = node["WindowHeight"].as<uint32_t>();
            if (node["TargetFPS"]) rhs.TargetFPS = node["TargetFPS"].as<uint32_t>();
            if (node["Scenes"]) rhs.Scenes = node["Scenes"].as<std::vector<std::string>>();
            if (node["StartupSceneIndex"]) rhs.StartupSceneIndex = node["StartupSceneIndex"].as<uint32_t>();
            return true;
        }
    };
}  // namespace YAML