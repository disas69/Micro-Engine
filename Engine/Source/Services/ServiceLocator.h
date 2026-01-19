#pragma once

#include <typeinfo>
#include <cassert>

#include "Service.h"
#include "Core/Types.h"

namespace Micro
{
    using TypeId = std::size_t;

    template <typename T>
    inline TypeId GetTypeId()
    {
        static const TypeId id = typeid(T).hash_code();
        return id;
    }

    class ServiceLocator
    {
    public:
        template <typename T>
        static void Register(std::unique_ptr<T> service);

        template <typename T>
        static T* Get();

        static void Shutdown();

    private:
        static std::unordered_map<TypeId, std::unique_ptr<Service>> m_Services;
    };

    template <typename T>
    void ServiceLocator::Register(std::unique_ptr<T> service)
    {
        static_assert(std::is_base_of_v<Service, T>, "ServiceLocator::Register<T>: T must derive from Service");

        const TypeId id = GetTypeId<T>();

        // Optional safety check
        assert(m_Services.find(id) == m_Services.end());

        m_Services[id] = std::move(service);
    }

    template <typename T>
    T* ServiceLocator::Get()
    {
        static_assert(std::is_base_of_v<Service, T>, "ServiceLocator::Get<T>: T must derive from Service");

        const TypeId id = GetTypeId<T>();

        auto it = m_Services.find(id);
        if (it == m_Services.end())
        {
            return nullptr;
        }

        return static_cast<T*>(it->second.get());
    }
}  // namespace Micro
