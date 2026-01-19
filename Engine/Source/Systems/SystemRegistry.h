#pragma once

#include "Systems/System.h"

namespace Micro
{
    class SystemRegistry
    {
    public:
        template<typename T>
        static void Register(const SystemPhase phase)
        {
            static_assert(std::is_base_of<System, T>::value, "T must be derived from System");

            m_Systems[phase].push_back(std::make_unique<T>());
        }

        static void Process(SystemPhase phase, GameBase* game);

    private:
        static std::unordered_map<SystemPhase, std::vector<std::unique_ptr<System>>> m_Systems;
    };
}  // namespace Micro
