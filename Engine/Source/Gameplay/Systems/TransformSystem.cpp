#include "TransformSystem.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Components/TransformComponent.h"
#include "TransformUtils.h"

namespace Micro
{
    void TransformSystem::Update(Scene* scene)
    {
        for (const auto& go : scene->GetGameObjects())
        {
            if (go->IsActive())
            {
                auto* transform = go->GetComponent<TransformComponent>();
                if (transform && transform->GetParent() == nullptr)
                {
                    UpdateRecursive(transform, MatrixIdentity());
                }
            }
        }
    }

    void TransformSystem::UpdateRecursive(TransformComponent* transform, const MMatrix& parentWorldMatrix)
    {
        if (!transform->GetGameObject()->IsActive())
        {
            return;
        }

        MMatrix worldMatrix;

        if (transform->IsDirty())
        {
            MMatrix localMatrix = transform->GetLocalMatrix();
            worldMatrix = MatrixMultiply(parentWorldMatrix, localMatrix);
            transform->SetWorldMatrix(worldMatrix);
        }
        else
        {
            worldMatrix = transform->GetWorldMatrix();
        }

        for (auto* child : transform->GetChildren())
        {
            UpdateRecursive(child, worldMatrix);
        }
    }

}  // namespace Micro