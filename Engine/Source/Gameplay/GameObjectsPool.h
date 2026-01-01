#pragma once

#include "GameObject.h"
#include "Memory/ArenaAllocator.h"

#include <vector>

namespace Micro
{
template <typename T>
class GameObjectsPool
{
public:
    GameObjectsPool(ArenaAllocator& arena) : m_arena(arena) {}
    GameObjectsPool(ArenaAllocator& arena, size_t initialSize) : m_arena(arena)
    {
        for (size_t i = 0; i < initialSize; ++i)
        {
            T* obj = m_arena.Allocate<T>(m_arena);
            if (obj != nullptr)
            {
                obj->Disable();
                m_pool.push_back(obj);
            }
        }
    }

    T* Acquire()
    {
        for (T* obj : m_pool)
        {
            if (!obj->IsActive())
            {
                obj->Enable();
                return obj;
            }
        }

        T* newObj = m_arena.Allocate<T>(m_arena);
        if (newObj != nullptr)
        {
            m_pool.push_back(newObj);
            newObj->Enable();
        }
        return newObj;
    }

    void Release(T* obj)
    {
        if (obj != nullptr)
        {
            obj->Disable();
        }
    }

    std::vector<T*> GetActiveObjects() const
    {
        std::vector<T*> activeObjects;
        for (T* obj : m_pool)
        {
            if (obj->IsActive())
            {
                activeObjects.push_back(obj);
            }
        }
        return activeObjects;
    }

private:
    ArenaAllocator& m_arena;
    std::vector<T*> m_pool;
};
}  // namespace Micro
