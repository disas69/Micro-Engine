#pragma once

namespace Micro
{
    class Service
    {
    public:
        Service() = default;
        virtual ~Service() = default;

        Service(const Service&) = delete;
        Service& operator=(const Service&) = delete;
        Service(Service&&) = delete;
        Service& operator=(Service&&) = delete;
    };
}
