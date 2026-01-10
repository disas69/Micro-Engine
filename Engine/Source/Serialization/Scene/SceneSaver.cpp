#include "SceneSaver.h"
#include "Gameplay/Scene.h"
#include "Gameplay/GameObject.h"
#include "Serialization/YAML/YamlComponentSerializer.h"
#include "yaml-cpp/yaml.h"

namespace Micro
{
    void SceneSaver::Save(const Scene* scene, const std::string& path)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "Version" << YAML::Value << 1;
        out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;

        for (const auto& go : scene->GetGameObjects())
        {
            out << YAML::BeginMap;
            out << YAML::Key << "ID" << YAML::Value << go->GetGUID();
            out << YAML::Key << "Name" << YAML::Value << go->GetName();
            out << YAML::Key << "Components" << YAML::Value << YAML::BeginSeq;

            for (const auto& component : go->GetAllComponents())
            {
                out << YAML::BeginMap;
                out << YAML::Key << component->GetTypeDescriptor().Name;
                out << YAML::Value;
                out << YAML::BeginMap;
                YAML::Node compNode;
                YamlComponentSerializer::Serialize(*component, compNode);
                out << compNode;
                out << YAML::EndMap;
                out << YAML::EndMap;
            }

            out << YAML::EndSeq;
            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;
        out << YAML::EndMap;

        SaveFileData(path.c_str(), (void*)out.c_str(), out.size());
    }
}  // namespace Micro