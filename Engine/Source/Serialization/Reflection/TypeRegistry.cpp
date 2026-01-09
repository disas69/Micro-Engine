#include "TypeRegistry.h"

namespace Micro
{
    std::unordered_map<std::string, TypeDescriptor*> TypeRegistry::s_Types;

    void TypeRegistry::Register(TypeDescriptor* type)
    {
        s_Types[type->Name] = type;
    }

    TypeDescriptor* TypeRegistry::Find(const std::string& name)
    {
        auto it = s_Types.find(name);
        if (it != s_Types.end())
        {
            return it->second;
        }
        return nullptr;
    }

}  // namespace Micro