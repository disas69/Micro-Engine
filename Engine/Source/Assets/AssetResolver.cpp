#include "AssetResolver.h"
#include "Services/ServiceLocator.h"
#include "Services/AssetsService.h"

namespace Micro
{
    template <>
    MTexture2D* AssetResolver<MTexture2D>::Resolve(const GUID& id)
    {
        return ServiceLocator::Get<AssetsService>()->GetTexture(id);
    }

    template <>
    MModel* AssetResolver<MModel>::Resolve(const GUID& id)
    {
        return ServiceLocator::Get<AssetsService>()->GetModel(id);
    }
}  // namespace Micro
