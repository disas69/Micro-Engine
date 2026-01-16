#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "Gameplay/Scene.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Systems/TransformSystem.h"

using namespace Micro;
using namespace Catch;

TEST_CASE("TransformComponent Initialization", "[Transform]")
{
    Scene scene;

    GameObject* go = scene.CreateGameObject("TestObject");
    auto transform = go->AddComponent<TransformComponent>();

    REQUIRE(transform->GetLocalPosition().x == Approx(0.0f));
    REQUIRE(transform->GetLocalPosition().y == Approx(0.0f));
    REQUIRE(transform->GetLocalPosition().z == Approx(0.0f));

    REQUIRE(transform->GetLocalRotation().x == Approx(0.0f));
    REQUIRE(transform->GetLocalRotation().y == Approx(0.0f));
    REQUIRE(transform->GetLocalRotation().z == Approx(0.0f));
    REQUIRE(transform->GetLocalRotation().w == Approx(1.0f));

    REQUIRE(transform->GetLocalScale().x == Approx(1.0f));
    REQUIRE(transform->GetLocalScale().y == Approx(1.0f));
    REQUIRE(transform->GetLocalScale().z == Approx(1.0f));
}

TEST_CASE("Local rotation rotates around local origin", "[Transform][Rotation]")
{
    Scene scene;

    GameObject* go = scene.CreateGameObject("Object");
    auto t = go->AddComponent<TransformComponent>();

    t->SetLocalPosition({5, 0, 0});
    t->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));

    TransformSystem::Update(&scene);

    MVector3 pos = t->GetWorldPosition();

    // Position must NOT change
    REQUIRE(pos.x == Approx(5.0f));
    REQUIRE(pos.y == Approx(0.0f));
    REQUIRE(pos.z == Approx(0.0f));
}

TEST_CASE("Forward vector matches rotation", "[Transform][Direction]")
{
    Scene scene;

    GameObject* go = scene.CreateGameObject("Object");
    auto t = go->AddComponent<TransformComponent>();

    t->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));
    TransformSystem::Update(&scene);

    MVector3 forward = t->GetForward();

    REQUIRE(forward.x == Approx(-1.0f).margin(0.001f));
    REQUIRE(forward.z == Approx(0.0f).margin(0.001f));
}

TEST_CASE("LookAt rotates transform toward target", "[Transform][LookAt]")
{
    Scene scene;

    GameObject* go = scene.CreateGameObject("Camera");
    auto t = go->AddComponent<TransformComponent>();

    t->SetLocalPosition({0, 0, 5});
    t->LookAt({0, 0, 0});

    TransformSystem::Update(&scene);

    MVector3 forward = t->GetForward();

    // Looking toward origin along -Z
    REQUIRE(forward.x == Approx(0.0f).margin(0.001f));
    REQUIRE(forward.y == Approx(0.0f).margin(0.001f));
    REQUIRE(forward.z == Approx(-1.0f).margin(0.001f));
}

TEST_CASE("LookAt works correctly with parent transform", "[Transform][LookAt][Hierarchy]")
{
    Scene scene;

    auto* parentGo = scene.CreateGameObject("Parent");
    auto* parent = parentGo->AddComponent<TransformComponent>();
    parent->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));

    auto* childGo = scene.CreateGameObject("Child");
    auto* child = childGo->AddComponent<TransformComponent>();
    child->SetParent(parent);
    child->SetLocalPosition({0, 0, 5});

    child->LookAt({0, 0, 0});
    TransformSystem::Update(&scene);

    MVector3 forward = child->GetForward();

    REQUIRE(forward.Length() > 0.99f);  // normalized
}

TEST_CASE("Parent dirty propagates to children", "[Transform][Dirty]")
{
    Scene scene;

    auto* parentGo = scene.CreateGameObject("Parent");
    auto* parent = parentGo->AddComponent<TransformComponent>();

    auto* childGo = scene.CreateGameObject("Child");
    auto* child = childGo->AddComponent<TransformComponent>();
    child->SetParent(parent);

    TransformSystem::Update(&scene);

    parent->SetLocalPosition({10, 0, 0});
    TransformSystem::Update(&scene);

    MVector3 childPos = child->GetWorldPosition();
    REQUIRE(childPos.x == Approx(10.0f));
}

TEST_CASE("Parent-Child full transformation composition", "[Transform]")
{
    Scene scene;

    auto* parentGo = scene.CreateGameObject("Parent");
    auto* parent = parentGo->AddComponent<TransformComponent>();

    auto* childGo = scene.CreateGameObject("Child");
    auto* child = childGo->AddComponent<TransformComponent>();
    child->SetParent(parent);

    // Parent transform
    parent->SetLocalPosition({10, 0, 0});
    parent->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));  // 90° Y
    parent->SetLocalScale({2, 2, 2});

    // Child transform
    child->SetLocalPosition({5, 0, 0});
    child->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));  // 90° Y
    child->SetLocalScale({1, 1, 1});

    TransformSystem::Update(&scene);

    SECTION("World position is correctly transformed")
    {
        MVector3 pos = child->GetWorldPosition();

        // Child local (5,0,0) rotated by parent => (0,0,-5), scaled => (0,0,-10), offset by parent
        REQUIRE(pos.x == Approx(10.0f));
        REQUIRE(pos.y == Approx(0.0f));
        REQUIRE(pos.z == Approx(-10.0f));
    }

    SECTION("World rotation is correctly combined")
    {
        MVector3 forward = child->GetForward();

        // Parent Y90 + Child Y90 => 180° => forward = +Z
        REQUIRE(forward.x == Approx(0.0f).margin(0.001f));
        REQUIRE(forward.y == Approx(0.0f).margin(0.001f));
        REQUIRE(forward.z == Approx(1.0f).margin(0.001f));
    }

    SECTION("World scale is correctly propagated")
    {
        MVector3 scale = child->GetWorldScale();

        REQUIRE(scale.x == Approx(2.0f));
        REQUIRE(scale.y == Approx(2.0f));
        REQUIRE(scale.z == Approx(2.0f));
    }
}

TEST_CASE("Grandchild transform composition (position, rotation, scale)", "[Transform]")
{
    Scene scene;

    auto* parentGo = scene.CreateGameObject("Parent");
    auto* parent = parentGo->AddComponent<TransformComponent>();

    auto* childGo = scene.CreateGameObject("Child");
    auto* child = childGo->AddComponent<TransformComponent>();
    child->SetParent(parent);

    auto* grandChildGo = scene.CreateGameObject("GrandChild");
    auto* grandChild = grandChildGo->AddComponent<TransformComponent>();
    grandChild->SetParent(child);

    // Parent: translate + rotate + scale
    parent->SetLocalPosition({10, 0, 0});
    parent->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));  // Y 90°
    parent->SetLocalScale({2, 1, 1});

    // Child: translate + rotate + scale
    child->SetLocalPosition({0, 5, 0});
    child->SetLocalRotation(QuaternionFromEuler(PI / 2, 0, 0));  // X 90°
    child->SetLocalScale({1, 2, 1});

    // Grandchild: translate only
    grandChild->SetLocalPosition({0, 0, 10});

    TransformSystem::Update(&scene);

    SECTION("World position is correctly composed")
    {
        MVector3 pos = grandChild->GetWorldPosition();

        REQUIRE(pos.x == Approx(10.0f));
        REQUIRE(pos.y == Approx(5.0f));
        REQUIRE(pos.z == Approx(-20.0f));
    }

    SECTION("World direction vectors are valid and orthogonal")
    {
        MVector3 f = grandChild->GetForward();
        MVector3 u = grandChild->GetUp();
        MVector3 r = grandChild->GetRight();

        REQUIRE(f.Length() == Approx(1.0f).margin(0.001f));
        REQUIRE(u.Length() == Approx(1.0f).margin(0.001f));
        REQUIRE(r.Length() == Approx(1.0f).margin(0.001f));

        REQUIRE(Vector3DotProduct(f, u) == Approx(0.0f).margin(0.001f));
        REQUIRE(Vector3DotProduct(f, r) == Approx(0.0f).margin(0.001f));
        REQUIRE(Vector3DotProduct(u, r) == Approx(0.0f).margin(0.001f));
    }

    SECTION("World scale is correctly propagated")
    {
        MVector3 scale = grandChild->GetWorldScale();

        REQUIRE(scale.x == Approx(2.0f));
        REQUIRE(scale.y == Approx(2.0f));
        REQUIRE(scale.z == Approx(1.0f));
    }
}

TEST_CASE("Detaching child preserves world transform", "[Transform][Detach]")
{
    Scene scene;

    auto* parentGo = scene.CreateGameObject("Parent");
    auto* parent = parentGo->AddComponent<TransformComponent>();
    parent->SetLocalPosition({10, 20, 30});
    parent->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));
    parent->SetLocalScale({2, 2, 2});

    auto* childGo = scene.CreateGameObject("Child");
    auto* child = childGo->AddComponent<TransformComponent>();
    child->SetLocalPosition({5, 0, 0});
    child->SetLocalRotation(QuaternionFromEuler(0, PI / 2, 0));
    child->SetLocalScale({1, 1, 1});
    child->SetParent(parent);

    TransformSystem::Update(&scene);

    const Vector3 worldPosBefore = child->GetWorldPosition();
    const Vector3 forwardBefore = child->GetForward();
    const Vector3 scaleBefore = child->GetWorldScale();

    // Detach
    child->SetParent(nullptr);
    TransformSystem::Update(&scene);

    SECTION("Parent is cleared")
    {
        REQUIRE(child->GetParent() == nullptr);
    }

    SECTION("World position is preserved")
    {
        MVector3 pos = child->GetWorldPosition();

        REQUIRE(pos.x == Approx(worldPosBefore.x));
        REQUIRE(pos.y == Approx(worldPosBefore.y));
        REQUIRE(pos.z == Approx(worldPosBefore.z));
    }

    SECTION("World orientation is preserved")
    {
        MVector3 forwardAfter = child->GetForward();

        REQUIRE(forwardAfter.x == Approx(forwardBefore.x).margin(0.001f));
        REQUIRE(forwardAfter.y == Approx(forwardBefore.y).margin(0.001f));
        REQUIRE(forwardAfter.z == Approx(forwardBefore.z).margin(0.001f));
    }

    SECTION("World scale is preserved")
    {
        MVector3 scale = child->GetWorldScale();

        REQUIRE(scale.x == Approx(scaleBefore.x));
        REQUIRE(scale.y == Approx(scaleBefore.y));
        REQUIRE(scale.z == Approx(scaleBefore.z));
    }

    SECTION("Child no longer follows parent")
    {
        parent->SetLocalPosition({100, 0, 0});
        TransformSystem::Update(&scene);

        MVector3 pos = child->GetWorldPosition();
        REQUIRE(pos.x == Approx(worldPosBefore.x));
    }
}
