#pragma once

#include "TypeDescriptor.h"

namespace Micro
{
    class TypeRegistry
    {
    public:
        static void Register(TypeDescriptor* type);
        static TypeDescriptor* Find(const std::string& name);

    private:
        static std::unordered_map<std::string, TypeDescriptor*> s_Types;
    };

}  // namespace Micro