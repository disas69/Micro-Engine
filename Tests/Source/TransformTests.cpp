#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "Gameplay/Scene.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Systems/TransformSystem.h"

using namespace Micro;
using namespace Catch;

TEST_CASE("Local rotation does not affect position", "[Transform]")
{
    Scene scene;
    GameObject* dummy = scene.CreateGameObject("Dummy");
    auto transform = dummy->AddComponent<TransformComponent>();

    transform->SetLocalPosition({5, 0, 0});

    Quaternion rot = QuaternionFromEuler(0, PI / 2, 0);
    transform->SetLocalRotation(rot);

    TransformSystem::Update(&scene);

    Vector3 pos = transform->GetWorldPosition();
    REQUIRE(pos.x == Approx(5.0f));
    REQUIRE(pos.z == Approx(0.0f));
}
