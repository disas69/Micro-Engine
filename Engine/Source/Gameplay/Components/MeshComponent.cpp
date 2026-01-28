#include "MeshComponent.h"

namespace Micro
{
    MICRO_COMPONENT_IMPL(MeshComponent)
    MeshComponent::MeshComponent(GameObject* owner) : Component(owner)
    {
    }
}  // namespace Micro