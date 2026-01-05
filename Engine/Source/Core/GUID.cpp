#include "GUID.h"
#include <random>

namespace Micro
{
    static std::random_device s_randomDevice;
    static std::mt19937_64 s_engine(s_randomDevice());
    static std::uniform_int_distribution<uint64_t> s_uniformDistribution;

    GUID::GUID() : m_guid(s_uniformDistribution(s_engine)) {}

    GUID::GUID(uint64_t guid) : m_guid(guid) {}
}  // namespace Micro