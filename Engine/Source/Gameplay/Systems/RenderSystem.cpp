#include "RenderSystem.h"
#include "Gameplay/Scene.h"
#include "Gameplay/Components/MeshComponent.h"
#include "Gameplay/Components/SpriteComponent.h"
#include "Gameplay/Components/TextComponent.h"
#include "Gameplay/Components/TransformComponent.h"
#include "Gameplay/Components/ImageComponent.h"

namespace Micro
{
    void RenderSystem::Render(MCamera3D* camera, Scene* scene)
    {
        BeginMode3D(*camera);

        for (const auto& go : scene->GetGameObjects())
        {
            const auto* transform = go->GetComponent<TransformComponent>();
            if (transform == nullptr)
            {
                continue;
            }

            if (auto* mesh = go->GetComponent<MeshComponent>())
            {
                DrawMesh(*mesh->GetMesh(), *mesh->GetMaterial(), transform->GetWorldMatrix());
            }

            if (auto* sprite = go->GetComponent<SpriteComponent>())
            {
                const MVector3 up = {0.0f, 1.0f, 0.0f};
                const MVector3 scale = transform->GetLocalScale();
                const MVector2 size = {sprite->GetSourceRect().width * scale.x, sprite->GetSourceRect().height * scale.y};
                const MVector2 origin = size.Scale(0.5f);

                DrawBillboardPro(*camera, sprite->GetSpriteTexture(), sprite->GetSourceRect(), transform->GetLocalPosition(), up, size, origin,
                    transform->GetLocalRotation().y, sprite->GetColor());
            }
        }

        EndMode3D();

        for (const auto& go : scene->GetGameObjects())
        {
            const auto* transform = go->GetComponent<TransformComponent>();
            if (transform == nullptr)
            {
                continue;
            }

            if (auto* image = go->GetComponent<ImageComponent>())
            {
                MRectangle destRect = {transform->GetLocalPosition().x, transform->GetLocalPosition().y, image->GetSourceRect().width * transform->GetLocalScale().x,
                    image->GetSourceRect().height * transform->GetLocalScale().y};
                MVector2 origin = {0, 0};
                DrawTexturePro(image->GetTexture(), image->GetSourceRect(), destRect, origin, transform->GetLocalRotation().y, image->GetColor());
            }

            if (auto* text = go->GetComponent<TextComponent>())
            {
                DrawText(text->GetText(), transform->GetLocalPosition().x, transform->GetLocalPosition().y, text->GetFontSize(), text->GetColor());
            }
        }
    }
}  // namespace Micro