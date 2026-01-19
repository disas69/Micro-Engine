#pragma once

#include "Systems/System.h"

namespace Micro
{
    class TransformSystem : public System
    {
    public:
        void Process(GameBase* game) override;

        static void Process(const Scene* scene);

    private:
        static void UpdateRecursive(TransformComponent* transform, const MMatrix& parentWorldMatrix);
    };
}  // namespace Micro