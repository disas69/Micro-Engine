#pragma once

#include <cstdint>

namespace Micro
{
    class GUID
    {
    public:
        GUID();
        GUID(uint64_t guid);
        GUID(const GUID&) = default;

        operator uint64_t() const { return m_Guid; }

        bool IsValid() const { return m_Guid != 0; }

    private:
        uint64_t m_Guid = 0;
    };
}  // namespace Micro

namespace std
{
    template <>
    struct hash<Micro::GUID>
    {
        std::size_t operator()(const Micro::GUID& guid) const { return hash<uint64_t>()((uint64_t)guid); }
    };
}  // namespace std