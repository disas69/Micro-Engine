#pragma once

#include "yaml-cpp/yaml.h"
#include "Gameplay/Components/Component.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
    class YamlComponentSerializer
    {
    public:
        static void Serialize(const Component& component, YAML::Node& out);
        static void Deserialize(GameObject& owner, const YAML::Node& in);
    };

}  // namespace Micro