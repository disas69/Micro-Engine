#include "YamlComponentSerializer.h"
#include "Serialization/Reflection/TypeRegistry.h"
#include "Core/GUID.h"

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
        const auto it = in.begin();
        const std::string componentName = it->first.as<std::string>();
        const YAML::Node& componentData = it->second;

        TypeDescriptor* typeDesc = TypeRegistry::Find(componentName);
        if (typeDesc == nullptr)
        {
            MICRO_LOG_WARNING("Component type not found: " + componentName);
            return;
        }

        Component* component = owner.GetComponent(typeDesc->Name);
        if (component == nullptr) component = typeDesc->Create(owner);

        for (const auto& field : typeDesc->Fields)
        {
            const YAML::Node fieldNode = componentData[field.Name];
            if (!fieldNode) continue;

            auto accessor = reinterpret_cast<MemberAccessor>(field.MemberPtr);
            void* fieldPtr = accessor(component);

            switch (field.Type)
            {
                case FieldType::Int: *static_cast<int*>(fieldPtr) = fieldNode.as<int>(); break;
                case FieldType::Float: *static_cast<float*>(fieldPtr) = fieldNode.as<float>(); break;
                case FieldType::Bool: *static_cast<bool*>(fieldPtr) = fieldNode.as<bool>(); break;
                case FieldType::String: *static_cast<std::string*>(fieldPtr) = fieldNode.as<std::string>(); break;
                case FieldType::Vector2: *static_cast<MVector2*>(fieldPtr) = fieldNode.as<MVector2>(); break;
                case FieldType::Vector3: *static_cast<MVector3*>(fieldPtr) = fieldNode.as<MVector3>(); break;
                case FieldType::Vector4: *static_cast<MQuaternion*>(fieldPtr) = fieldNode.as<MQuaternion>(); break;
                case FieldType::Color: *static_cast<MColor*>(fieldPtr) = fieldNode.as<MColor>(); break;
                case FieldType::Rect: *static_cast<MRectangle*>(fieldPtr) = fieldNode.as<MRectangle>(); break;
            }
        }
    }
}  // namespace Micro
