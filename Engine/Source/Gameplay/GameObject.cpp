#include "GameObject.h"

#include <utility>

namespace Micro
{
    GameObject::GameObject(std::string name, GUID guid) : m_name(std::move(name)), m_guid(guid) {}
}  // namespace Micro
