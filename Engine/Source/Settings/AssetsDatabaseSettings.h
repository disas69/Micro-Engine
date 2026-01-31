#pragma once

#include <yaml-cpp/yaml.h>

#include "Settings.h"
#include "Assets/AssetsDatabase.h"

namespace Micro
{
    struct AssetsDatabaseSettings : Settings
    {
        AssetsDatabase AssetsDB;

        std::string GetFileName() override { return "AssetDatabase.asset"; }
    };
}  // namespace Micro

namespace YAML
{
    template <>
    struct convert<Micro::AssetsDatabaseSettings>
    {
        static Node encode(const Micro::AssetsDatabaseSettings& rhs)
        {
            Node node;
            node["Assets"] = YAML::Node(YAML::NodeType::Map);
            for (const auto& [guid, path] : rhs.AssetsDB.GetAssets())
            {
                node["Assets"][static_cast<uint64_t>(guid)] = path;
            }
            return node;
        }

        static bool decode(const Node& node, Micro::AssetsDatabaseSettings& rhs)
        {
            if (node["Assets"])
            {
                for (YAML::const_iterator it = node["Assets"].begin(); it != node["Assets"].end(); ++it)
                {
                    Micro::GUID guid(it->first.as<uint64_t>());
                    std::string path = it->second.as<std::string>();
                    rhs.AssetsDB.AddAsset(guid, path);
                }
            }
            return true;
        }
    };
}  // namespace YAML