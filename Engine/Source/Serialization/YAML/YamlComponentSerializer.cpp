#include "YamlComponentSerializer.h"
#include "Serialization/Reflection/TypeRegistry.h"
#include "Core/GUID.h"

namespace YAML
{
    template <>
    struct convert<Micro::GUID>
    {
        static Node encode(const Micro::GUID& guid)
        {
            Node node;
            node.push_back((uint64_t)guid);
            return node;
        }

        static bool decode(const Node& node, Micro::GUID& guid)
        {
            if (!node.IsScalar()) return false;

            guid = Micro::GUID(node.as<uint64_t>());
            return true;
        }
    };

    template <>
    struct convert<Micro::MVector2>
    {
        static Node encode(const Micro::MVector2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }

        static bool decode(const Node& node, Micro::MVector2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MVector3>
    {
        static Node encode(const Micro::MVector3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node& node, Micro::MVector3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MQuaternion>
    {
        static Node encode(const Micro::MQuaternion& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }

        static bool decode(const Node& node, Micro::MQuaternion& rhs)
        {
            if (!node.IsSequence() || node.size() != 4) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}  // namespace YAML

namespace Micro
{
    void YamlComponentSerializer::Serialize(const Component& component, YAML::Node& out)
    {
        const auto& typeDesc = component.GetTypeDescriptor();

        for (const auto& field : typeDesc.Fields)
        {
            const char* fieldPtr = reinterpret_cast<const char*>(&component) + field.Offset;

            switch (field.Type)
            {
                case FieldType::Int: out[field.Name] = *reinterpret_cast<const int*>(fieldPtr); break;
                case FieldType::Float: out[field.Name] = *reinterpret_cast<const float*>(fieldPtr); break;
                case FieldType::Bool: out[field.Name] = *reinterpret_cast<const bool*>(fieldPtr); break;
                case FieldType::String: out[field.Name] = *reinterpret_cast<const std::string*>(fieldPtr); break;
                case FieldType::Vector2: out[field.Name] = *reinterpret_cast<const MVector2*>(fieldPtr); break;
                case FieldType::Vector3: out[field.Name] = *reinterpret_cast<const MVector3*>(fieldPtr); break;
                case FieldType::Vector4: out[field.Name] = *reinterpret_cast<const MQuaternion*>(fieldPtr); break;
            }
        }
    }

    void YamlComponentSerializer::Deserialize(GameObject& owner, const YAML::Node& in)
    {
        const std::string componentName = in.begin()->first.as<std::string>();
        const YAML::Node& componentData = in.begin()->second;

        TypeDescriptor* typeDesc = TypeRegistry::Find(componentName);
        if (typeDesc == nullptr)
        {
            MICRO_LOG_WARNING("Component type not found: " + componentName);
            return;
        }

        Component* component = owner.GetComponent(typeDesc->Name);
        if (component == nullptr)
        {
            component = typeDesc->Create(owner);
        }

        for (const auto& field : typeDesc->Fields)
        {
            if (componentData[field.Name])
            {
                char* fieldPtr = reinterpret_cast<char*>(component) + field.Offset;

                switch (field.Type)
                {
                    case FieldType::Int: *reinterpret_cast<int*>(fieldPtr) = componentData[field.Name].as<int>(); break;
                    case FieldType::Float: *reinterpret_cast<float*>(fieldPtr) = componentData[field.Name].as<float>(); break;
                    case FieldType::Bool: *reinterpret_cast<bool*>(fieldPtr) = componentData[field.Name].as<bool>(); break;
                    case FieldType::String: *reinterpret_cast<std::string*>(fieldPtr) = componentData[field.Name].as<std::string>(); break;
                    case FieldType::Vector2: *reinterpret_cast<MVector2*>(fieldPtr) = componentData[field.Name].as<MVector2>(); break;
                    case FieldType::Vector3: *reinterpret_cast<MVector3*>(fieldPtr) = componentData[field.Name].as<MVector3>(); break;
                    case FieldType::Vector4: *reinterpret_cast<MQuaternion*>(fieldPtr) = componentData[field.Name].as<MQuaternion>(); break;
                }
            }
        }
    }
}  // namespace Micro