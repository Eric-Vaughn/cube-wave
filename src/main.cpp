#include <string>
#include <raylib.h>

const unsigned int FPS = 60;

int main()
{
    InitWindow(800, 800, "Cube Wave"); // Create window
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {

        // Drawing
        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        // TODO: Draw objects here

        EndDrawing();
    }
    CloseWindow(); // Must close window

    return 0;
}