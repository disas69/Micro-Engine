#include "GameBase.h"

using namespace Micro;

void GameBase::Init()
{
    Resize(GetScreenWidth(), GetScreenHeight());
}

void GameBase::Resize(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}