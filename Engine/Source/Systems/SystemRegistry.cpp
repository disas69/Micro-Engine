#include "SystemRegistry.h"

namespace Micro
{
    std::unordered_map<SystemPhase, std::vector<std::unique_ptr<System>>> SystemRegistry::m_Systems;

    void SystemRegistry::Process(const SystemPhase phase, GameBase* game)
    {
        if (m_Systems.find(phase) != m_Systems.end())
        {
            for (const auto& system : m_Systems.at(phase))
            {
                system->Process(game);
            }
        }
    }
}  // namespace Micro
