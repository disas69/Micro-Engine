#pragma once

#include "TypeDescriptor.h"
#include "Gameplay/GameObject.h"

#define MICRO_FIELD(type, name, fieldType) {#name, offsetof(type, name), fieldType}

#define MICRO_COMPONENT(type)                                                                                                                                       \
public:                                                                                                                                                             \
    static Micro::TypeDescriptor& GetType();                                                                                                                        \
    virtual Micro::TypeDescriptor& GetTypeDescriptor() const override                                                                                               \
    {                                                                                                                                                               \
        return GetType();                                                                                                                                           \
    }

#define MICRO_COMPONENT_IMPL(type, ...)                                                                                                                             \
    Micro::TypeDescriptor& type::GetType()                                                                                                                          \
    {                                                                                                                                                               \
        static Micro::TypeDescriptor typeDesc = {                                                                                                                   \
            #type, sizeof(type), {__VA_ARGS__}, [](GameObject& owner) -> Micro::Component* { return owner.AddComponent<type>(); }};                                 \
        return typeDesc;                                                                                                                                            \
    }
