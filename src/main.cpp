#include <string>
#include <raylib.h>

const unsigned int FPS = 60;

int main()
{
    InitWindow(800, 800, "Cube Wave"); // Create window
    SetTargetFPS(FPS);

    // Create a 3D camera
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};     // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};         // Camera up vector
    camera.fovy = 45.0f;                             // Field of view
    camera.projection = CAMERA_PERSPECTIVE;          // Projection type

    // Main game loop
    while (!WindowShouldClose())
    {

        // Drawing
        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        BeginMode3D(camera); // Begin 3D mode

        // Draw a solid cube (Position, Width, Height, Length, Color)
        DrawCube((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, RED);
        // Draw the cube's wireframe outline on top
        DrawCubeWires((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, MAROON);

        // Draw a reference grid on the ground
        DrawGrid(10, 1.0f);

        EndMode3D(); // End 3D mode

        DrawFPS(10, 10); // Put FPS on screen

        EndDrawing(); // End drawing
    }
    CloseWindow(); // Must close window

    return 0;
}