#pragma once

#include "Assets/AssetRef.h"
#include "yaml-cpp/yaml.h"
#include "Gameplay/Components/Component.h"
#include "Gameplay/GameObject.h"

namespace Micro
{
    class YamlComponentSerializer
    {
    public:
        static void Serialize(const Component& component, YAML::Node& out);
        static void Deserialize(GameObject& owner, const YAML::Node& in);
    };

}  // namespace Micro

namespace YAML
{
    template <>
    struct convert<Micro::GUID>
    {
        static Node encode(const Micro::GUID& guid)
        {
            return Node(static_cast<uint64_t>(guid));
        }

        static bool decode(const Node& node, Micro::GUID& guid)
        {
            if (!node.IsScalar()) return false;
            guid = Micro::GUID(node.as<uint64_t>());
            return true;
        }
    };

    template <>
    struct convert<Micro::MVector2>
    {
        static Node encode(const Micro::MVector2& v)
        {
            Node node(NodeType::Sequence);
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(v.x);
            node.push_back(v.y);
            return node;
        }

        static bool decode(const Node& node, Micro::MVector2& v)
        {
            if (!node.IsSequence() || node.size() != 2) return false;
            v.x = node[0].as<float>();
            v.y = node[1].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MVector3>
    {
        static Node encode(const Micro::MVector3& v)
        {
            Node node(NodeType::Sequence);
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(v.x);
            node.push_back(v.y);
            node.push_back(v.z);
            return node;
        }

        static bool decode(const Node& node, Micro::MVector3& v)
        {
            if (!node.IsSequence() || node.size() != 3) return false;
            v.x = node[0].as<float>();
            v.y = node[1].as<float>();
            v.z = node[2].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MQuaternion>
    {
        static Node encode(const Micro::MQuaternion& q)
        {
            Node node(NodeType::Sequence);
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(q.x);
            node.push_back(q.y);
            node.push_back(q.z);
            node.push_back(q.w);
            return node;
        }

        static bool decode(const Node& node, Micro::MQuaternion& q)
        {
            if (!node.IsSequence() || node.size() != 4) return false;
            q.x = node[0].as<float>();
            q.y = node[1].as<float>();
            q.z = node[2].as<float>();
            q.w = node[3].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::MColor>
    {
        static Node encode(const Micro::MColor& c)
        {
            Node node(NodeType::Sequence);
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(static_cast<int>(c.r));
            node.push_back(static_cast<int>(c.g));
            node.push_back(static_cast<int>(c.b));
            node.push_back(static_cast<int>(c.a));
            return node;
        }

        static bool decode(const Node& node, Micro::MColor& c)
        {
            if (!node.IsSequence() || node.size() != 4) return false;
            c.r = static_cast<uint8_t>(node[0].as<int>());
            c.g = static_cast<uint8_t>(node[1].as<int>());
            c.b = static_cast<uint8_t>(node[2].as<int>());
            c.a = static_cast<uint8_t>(node[3].as<int>());
            return true;
        }
    };

    template <>
    struct convert<Micro::MRectangle>
    {
        static Node encode(const Micro::MRectangle& r)
        {
            Node node(NodeType::Sequence);
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(r.x);
            node.push_back(r.y);
            node.push_back(r.width);
            node.push_back(r.height);
            return node;
        }

        static bool decode(const Node& node, Micro::MRectangle& r)
        {
            if (!node.IsSequence() || node.size() != 4) return false;
            r.x = node[0].as<float>();
            r.y = node[1].as<float>();
            r.width = node[2].as<float>();
            r.height = node[3].as<float>();
            return true;
        }
    };

    template <>
    struct convert<Micro::AssetRef>
    {
        static Node encode(const Micro::AssetRef& assetRef)
        {
            Node node;
            node["ID"] = assetRef.GetID();
            return node;
        }

        static bool decode(const Node& node, Micro::AssetRef& assetRef)
        {
            if (node["ID"])
            {
                assetRef = Micro::AssetRef(node["ID"].as<Micro::GUID>());
                return true;
            }
            return false;
        }
    };
}  // namespace YAML