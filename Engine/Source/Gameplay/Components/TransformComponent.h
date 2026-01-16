#pragma once

#include "Component.h"

namespace Micro
{
    class TransformComponent : public Component
    {
        MICRO_COMPONENT(TransformComponent)

        explicit TransformComponent(GameObject* owner);

        void OnDestroy() override;

        void SetLocalPosition(const MVector3& position);
        void SetLocalRotation(const MQuaternion& rotation);
        void SetLocalScale(const MVector3& scale);

        MVector3 GetLocalPosition() const { return m_LocalPosition; }
        MQuaternion GetLocalRotation() const { return m_LocalRotation; }
        MVector3 GetLocalScale() const { return m_LocalScale; }

        MMatrix GetWorldMatrix() const { return m_WorldMatrix; }
        void SetWorldMatrix(const MMatrix& matrix);
        MMatrix GetLocalMatrix() const;

        MVector3 GetWorldPosition();
        MQuaternion GetWorldRotation();
        MVector3 GetWorldScale();

        MVector3 GetRight();
        MVector3 GetUp();
        MVector3 GetForward();

        void Translate(const MVector3& delta);
        void Rotate(const MVector3& eulerAngles);
        void LookAt(const MVector3& target);

        void SetParent(TransformComponent* parent);
        TransformComponent* GetParent() const { return m_Parent; }

        const std::vector<TransformComponent*>& GetChildren() const { return m_Children; }
        size_t GetChildrenCount() const { return m_Children.size(); }
        void ForEachChild(const std::function<void(TransformComponent*)>& func) const;

        void MarkDirty();
        bool IsDirty() const { return m_IsDirty; }

    private:
        MMatrix m_WorldMatrix;
        std::vector<TransformComponent*> m_Children;

        MVector3 m_LocalPosition;
        MQuaternion m_LocalRotation;
        MVector3 m_LocalScale;

        TransformComponent* m_Parent = nullptr;

        bool m_IsDirty;

        void AddChild(TransformComponent* child);
        void RemoveChild(TransformComponent* child);
        void ForceUpdateWorldMatrix();
    };
}  // namespace Micro
