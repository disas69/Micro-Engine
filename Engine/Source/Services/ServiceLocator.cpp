#include "ServiceLocator.h"

namespace Micro
{
    std::unordered_map<TypeId, std::unique_ptr<Service>> ServiceLocator::m_Services;

    void ServiceLocator::Shutdown()
    {
        m_Services.clear();
    }
}  // namespace Micro
