#pragma once

#include "Component.h"
#include "Core/Types.h"

namespace Micro
{
    class TextComponent : public Component
    {
    public:
        TextComponent() = default;

        std::string& GetText() { return m_text; }
        void SetText(const std::string& text) { m_text = text; }

        float GetFontSize() const { return m_fontSize; }
        void SetFontSize(float fontSize) { m_fontSize = fontSize; }

        MColor& GetColor() { return m_color; }
        void SetColor(const MColor& color) { m_color = color; }

    private:
        std::string m_text;
        float m_fontSize = 20.0f;
        MColor m_color = MColor::White();
    };
}  // namespace Micro
