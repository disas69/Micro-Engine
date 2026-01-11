#include "SceneSaver.h"
#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Serialization/YAML/YamlComponentSerializer.h"
#include "yaml-cpp/yaml.h"

namespace Micro
{
    void SceneSaver::Save(const Scene* scene, const std::string& path)
    {
        YAML::Node root;
        YAML::Node sceneNode;
        YAML::Node objectsNode(YAML::NodeType::Sequence);

        sceneNode["Version"] = 1;

        for (const auto& go : scene->GetGameObjects())
        {
            YAML::Node goNode;
            goNode["ID"] = go->GetGUID();
            goNode["Name"] = go->GetName();

            YAML::Node componentsNode(YAML::NodeType::Sequence);

            for (const auto& component : go->GetAllComponents())
            {
                YAML::Node componentNode;
                YAML::Node componentData;

                YamlComponentSerializer::Serialize(*component, componentData);

                componentNode[component->GetTypeDescriptor().Name] = componentData;
                componentsNode.push_back(componentNode);
            }

            goNode["Components"] = componentsNode;
            objectsNode.push_back(goNode);
        }

        sceneNode["GameObjects"] = objectsNode;
        root["Scene"] = sceneNode;

        YAML::Emitter out;
        out << root;

        SaveFileData(path.c_str(), (void*)out.c_str(), out.size());
    }

}  // namespace Micro