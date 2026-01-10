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

    template <>
    struct convert<Micro::MColor>
    {
        static Node encode(const Micro::MColor& rhs)
        {
            Node node;
            node.push_back(rhs.r);
            node.push_back(rhs.g);
            node.push_back(rhs.b);
            node.push_back(rhs.a);
            return node;
        }

        static bool decode(const Node& node, Micro::MColor& rhs)
        {
            if (!node.IsSequence() || node.size() != 4) return false;

            rhs.r = node[0].as<float>();
            rhs.g = node[1].as<float>();
            rhs.b = node[2].as<float>();
            rhs.a = node[3].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MRectangle>
    {
        static Node encode(const Micro::MRectangle& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.width);
            node.push_back(rhs.height);
            return node;
        }

        static bool decode(const Node& node, Micro::MRectangle& rhs)
        {
            if (!node.IsSequence() || node.size() != 4) return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.width = node[2].as<float>();
            rhs.height = node[3].as<float>();
            return true;
        }
    };

}  // namespace YAML

namespace Micro
{
    using MemberAccessor = void* (*)(void*);

    void YamlComponentSerializer::Serialize(const Component& component, YAML::Node& out)
    {
        const auto& typeDesc = component.GetTypeDescriptor();

        for (const auto& field : typeDesc.Fields)
        {
            auto accessor = reinterpret_cast<MemberAccessor>(field.MemberPtr);
            const void* fieldPtr = accessor((void*)&component);

            switch (field.Type)
            {
                case FieldType::Int: out[field.Name] = *static_cast<const int*>(fieldPtr); break;
                case FieldType::Float: out[field.Name] = *static_cast<const float*>(fieldPtr); break;
                case FieldType::Bool: out[field.Name] = *static_cast<const bool*>(fieldPtr); break;
                case FieldType::String: out[field.Name] = *static_cast<const std::string*>(fieldPtr); break;
                case FieldType::Vector2: out[field.Name] = *static_cast<const MVector2*>(fieldPtr); break;
                case FieldType::Vector3: out[field.Name] = *static_cast<const MVector3*>(fieldPtr); break;
                case FieldType::Vector4: out[field.Name] = *static_cast<const MQuaternion*>(fieldPtr); break;
                case FieldType::Color: out[field.Name] = *static_cast<const MColor*>(fieldPtr); break;
                case FieldType::Rect: out[field.Name] = *static_cast<const MRectangle*>(fieldPtr); break;
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
                auto accessor = reinterpret_cast<MemberAccessor>(field.MemberPtr);
                void* fieldPtr = accessor(component);

                switch (field.Type)
                {
                    case FieldType::Int: *static_cast<int*>(fieldPtr) = componentData[field.Name].as<int>(); break;
                    case FieldType::Float: *static_cast<float*>(fieldPtr) = componentData[field.Name].as<float>(); break;
                    case FieldType::Bool: *static_cast<bool*>(fieldPtr) = componentData[field.Name].as<bool>(); break;
                    case FieldType::String: *static_cast<std::string*>(fieldPtr) = componentData[field.Name].as<std::string>(); break;
                    case FieldType::Vector2: *static_cast<MVector2*>(fieldPtr) = componentData[field.Name].as<MVector2>(); break;
                    case FieldType::Vector3: *static_cast<MVector3*>(fieldPtr) = componentData[field.Name].as<MVector3>(); break;
                    case FieldType::Vector4: *static_cast<MQuaternion*>(fieldPtr) = componentData[field.Name].as<MQuaternion>(); break;
                    case FieldType::Color: *static_cast<MColor*>(fieldPtr) = componentData[field.Name].as<MColor>(); break;
                    case FieldType::Rect: *static_cast<MRectangle*>(fieldPtr) = componentData[field.Name].as<MRectangle>(); break;
                }
            }
        }
    }
}  // namespace Micro