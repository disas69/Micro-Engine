#pragma once

#include "Component.h"

namespace Micro
{
    class TextComponent : public Component
    {
        MICRO_COMPONENT(TextComponent)

        std::string& GetText() { return m_Text; }
        void SetText(const std::string& text) { m_Text = text; }

        float GetFontSize() const { return m_FontSize; }
        void SetFontSize(float fontSize) { m_FontSize = fontSize; }

        MColor& GetColor() { return m_Color; }
        void SetColor(const MColor& color) { m_Color = color; }

    private:
        std::string m_Text;
        float m_FontSize = 20.0f;
        MColor m_Color = MColor::White();
    };
}  // namespace Micro
