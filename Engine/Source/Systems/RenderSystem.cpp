#include "RenderSystem.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Components/CameraComponent.h"
#include "Gameplay/Components/ImageComponent.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/SpriteComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "Gameplay/Components/TransformComponent.h"

namespace Micro
{
    void RenderSystem::Process(GameBase* game)
    {
        auto camera = game->GetMainCamera();
        auto scene = game->GetScene();
        if (camera == nullptr || scene == nullptr)
        {
            MICRO_LOG_ERROR("RenderSystem::Render - Invalid camera or scene");
            return;
        }

        BeginMode3D(*camera);

        for (const auto& go : scene->GetGameObjects())
        {
            if (!go->IsActive())
            {
                continue;
            }

            const auto* transform = go->GetComponent<TransformComponent>();
            if (transform == nullptr)
            {
                continue;
            }

            if (auto* mesh = go->GetComponent<MeshComponent>())
            {
                if (mesh->IsEnabled())
                {
                    DrawMesh(*mesh->GetMesh(), *mesh->GetMaterial(), transform->GetWorldMatrix());
                }
            }

            if (auto* sprite = go->GetComponent<SpriteComponent>())
            {
                if (sprite->IsEnabled())
                {
                    MVector3 position, scale;
                    MQuaternion rotation;
                    MatrixDecompose(transform->GetWorldMatrix(), &position, &rotation, &scale);

                    const MVector3 up = {0.0f, 1.0f, 0.0f};
                    const MVector2 size = {sprite->GetSourceRect().width * scale.x, sprite->GetSourceRect().height * scale.y};
                    const MVector2 origin = Vector2Scale(size, 0.5f);

                    MVector3 euler_angles = QuaternionToEuler(rotation);
                    DrawBillboardPro(*camera, sprite->GetSpriteTexture(), sprite->GetSourceRect(), position, up, size, origin, euler_angles.z, sprite->GetColor());
                }
            }
        }

        EndMode3D();

        for (const auto& go : scene->GetGameObjects())
        {
            if (!go->IsActive())
            {
                continue;
            }

            auto* transform = go->GetComponent<TransformComponent>();
            if (transform == nullptr)
            {
                continue;
            }

            if (auto* image = go->GetComponent<ImageComponent>())
            {
                if (image->IsEnabled())
                {
                    MVector3 position, scale;
                    MQuaternion rotation;
                    MatrixDecompose(transform->GetWorldMatrix(), &position, &rotation, &scale);

                    MVector2 origin = {0, 0};
                    MVector3 euler_angles = QuaternionToEuler(rotation);
                    MRectangle destRect = {position.x, position.y, image->GetSourceRect().width * scale.x, image->GetSourceRect().height * scale.y};

                    DrawTexturePro(image->GetTexture(), image->GetSourceRect(), destRect, origin, euler_angles.z * RAD2DEG, image->GetColor());
                }
            }

            if (auto* text = go->GetComponent<TextComponent>())
            {
                if (text->IsEnabled())
                {
                    MVector3 text_position = transform->GetWorldPosition();
                    DrawText(text->GetText(), text_position.x, text_position.y, text->GetFontSize(), text->GetColor());
                }
            }
        }
    }
}  // namespace Micro