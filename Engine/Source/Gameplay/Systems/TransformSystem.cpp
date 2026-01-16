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

        if (transform->IsDirty())
        {
            MMatrix localMatrix = transform->GetLocalMatrix();
            MMatrix worldMatrix = MatrixMultiply(localMatrix, parentWorldMatrix);
            transform->SetWorldMatrix(worldMatrix);
        }

        for (auto* child : transform->GetChildren())
        {
            UpdateRecursive(child, transform->GetWorldMatrix());
        }
    }

}  // namespace Micro