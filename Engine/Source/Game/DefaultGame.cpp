#include "DefaultGame.h"

using namespace Micro;

DefaultGame::DefaultGame(ArenaAllocator& persistentArena) : GameBase(persistentArena)
{
    m_windowTitle = "Default Game";
}

void DefaultGame::OnInit()
{

}

void DefaultGame::Update(ArenaAllocator& frameArena, float deltaTime)
{

}

void DefaultGame::Render()
{
    int textWidth = MeasureText("Default game is running!", 20);
    DrawText("Default game is running!", m_screenWidth / 2.0f - textWidth / 2.0f, m_screenHeight / 2.0f - 10, 20, LIGHTGRAY);
}