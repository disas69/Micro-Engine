#pragma once

namespace Micro
{
    class GameObject;
    class Component;

    enum class FieldType : uint8_t
    {
        Int = 0,
        Float = 1,
        Bool = 2,
        String = 3,
        Vector2 = 4,
        Vector3 = 5,
        Vector4 = 6,
    };

    struct FieldDescriptor
    {
        const char* Name;
        size_t Offset;
        FieldType Type;
    };

    struct TypeDescriptor
    {
        const char* Name;
        size_t Size;
        std::vector<FieldDescriptor> Fields;
        std::function<Component*(GameObject&)> Create;
    };

}  // namespace Micro