#include "Editor.h"
#include "Game/DefaultGame.h"

int main()
{
    Micro::Engine engine;
    engine.Load<Micro::DefaultGame>();

    Micro::Editor editor;
    return editor.Run(&engine);
}