#include "SceneLoader.h"
#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Serialization/YAML/YamlComponentSerializer.h"
#include "yaml-cpp/yaml.h"
#include "Core/GUID.h"
#include "Core/Log.h"

namespace Micro
{
    void SceneLoader::Load(const std::string& path, Scene* scene)
    {
        YAML::Node data = YAML::LoadFile(path);
        if (!data["Scene"])
        {
            return;
        }

        std::vector<std::pair<TransformComponent*, GUID>> unresolvedTransforms;

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

                        const auto& componentData = compIt->begin()->second;
                        if (componentData["Parent"])
                        {
                            GUID parentGuid = componentData["Parent"].as<GUID>();
                            if (parentGuid.IsValid())
                            {
                                if (auto* transform = go->GetComponent<TransformComponent>())
                                {
                                    unresolvedTransforms.emplace_back(transform, parentGuid);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (const auto& pair : unresolvedTransforms)
        {
            TransformComponent* childTransform = pair.first;
            GUID parentGuid = pair.second;

            GameObject* parentGameObject = scene->FindGameObjectByGUID(parentGuid);
            if (parentGameObject != nullptr)
            {
                if (auto* parentTransform = parentGameObject->GetComponent<TransformComponent>())
                {
                    childTransform->SetParent(parentTransform);
                }
                else
                {
                    MICRO_LOG_ERROR(std::string("Parent GameObject with GUID %llu found, but it has no TransformComponent.", (uint64_t)parentGuid));
                }
            }
            else
            {
                MICRO_LOG_WARNING(std::string("Parent GameObject with GUID %llu not found for child object", (uint64_t)parentGuid));
            }
        }
    }
}  // namespace Micro