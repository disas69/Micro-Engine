#include "SceneLoader.h"
#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Serialization/YAML/YamlComponentSerializer.h"
#include "yaml-cpp/yaml.h"
#include "Core/GUID.h"

namespace Micro
{
    void SceneLoader::Load(const std::string& path, Scene* scene)
    {
        YAML::Node data = YAML::LoadFile(path);
        if (!data["Scene"])
        {
            return;
        }

        YAML::Node sceneNode = data["Scene"];
        if (sceneNode["GameObjects"])
        {
            YAML::Node gameObjectsNode = sceneNode["GameObjects"];
            for (YAML::const_iterator it = gameObjectsNode.begin(); it != gameObjectsNode.end(); ++it)
            {
                YAML::Node goNode = *it;
                GUID guid = goNode["ID"].as<uint64_t>();
                std::string name = goNode["Name"].as<std::string>();

                GameObject* go = scene->CreateGameObject(name, guid);

                if (goNode["Components"])
                {
                    YAML::Node componentsNode = goNode["Components"];
                    for (YAML::const_iterator compIt = componentsNode.begin(); compIt != componentsNode.end(); ++compIt)
                    {
                        YamlComponentSerializer::Deserialize(*go, *compIt);
                    }
                }
            }
        }
    }
}  // namespace Micro