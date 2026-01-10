#pragma once

#include "Core/Log.h"

#include <new>
#include <cstdlib>

namespace Micro
{
    class ArenaAllocator
    {
    public:
        explicit ArenaAllocator(size_t size) : m_Size(size), m_Offset(0)
        {
            m_Buffer = static_cast<char*>(std::malloc(size));
            MICRO_LOG_INFO(TextFormat("ArenaAllocator: allocated buffer of %d", size));
        }

        ~ArenaAllocator()
        {
            std::free(m_Buffer);
            MICRO_LOG_INFO(TextFormat("ArenaAllocator: released buffer of %d", m_Size));
        }

        void* Allocate(size_t size)
        {
            if (m_Offset + size > m_Size)
            {
                MICRO_LOG_ERROR(TextFormat("ArenaAllocator: allocation out of bounds"));
                return nullptr;
            }

            void* ptr = m_Buffer + m_Offset;
            m_Offset += size;

            MICRO_LOG_INFO(TextFormat("ArenaAllocator: allocated size of %d, total allocation is %d", size, m_Offset));

            return ptr;
        }

        template <typename T, typename... Args>
        T* Allocate(Args&&... args)
        {
            void* memory = Allocate(sizeof(T));
            if (memory != nullptr)
            {
                return new (memory) T(std::forward<Args>(args)...);
            }

            return nullptr;
        }

        template <typename T, typename... Args>
        T* AllocateArray(size_t size, Args&&... args)
        {
            void* memory = Allocate(sizeof(T) * size);
            if (memory != nullptr)
            {
                T* array = static_cast<T*>(memory);
                for (size_t i = 0; i < size; ++i)
                {
                    new (&array[i]) T(std::forward<Args>(args)...);
                }

                return array;
            }

            return nullptr;
        }

        void Reset()
        {
            m_Offset = 0;
            MICRO_LOG_INFO("ArenaAllocator: reset buffer");
        }

    private:
        size_t m_Size;
        size_t m_Offset;
        char* m_Buffer;
    };
}  // namespace Micro
