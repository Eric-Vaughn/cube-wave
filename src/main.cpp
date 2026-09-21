#include <string>
#include <cmath>
#include <chrono>
#include <raylib.h>

const unsigned int FPS = 60;

// Helper function to get the current time in seconds
double getTimeInSeconds()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration<double>(duration).count();
}

// Helper function to convert degrees to radians
double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

int main()
{
    InitWindow(800, 800, "Cube Wave"); // Create window
    SetTargetFPS(FPS);

    // Create a 3D camera
    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector
    camera.fovy = 50.0f;                              // Field of view (in orthographic mode, fovy acts as the view size/zoom width)
    camera.projection = CAMERA_ORTHOGRAPHIC;          // Projection type

    // TEST
    const double SPEED_MULTIPLIER = 90.0; // Speed in degrees per second (90°/sec = full rotation in 4 seconds)

    double angleDegrees = 0.0;
    double lastTime = getTimeInSeconds();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Moving the cube up and down
        double currentTime = getTimeInSeconds();
        double deltaTime = currentTime - lastTime; // Calculate Delta Time (seconds passed since the last frame)
        lastTime = currentTime;

        // Increase angle based on time passed, not frame rate
        angleDegrees += SPEED_MULTIPLIER * deltaTime;

        // Wrap around 360 degrees (no precsision loss)
        if (angleDegrees >= 360.0)
        {
            angleDegrees = 0.0;
        }

        // Convert to Radians & Calculate Sine Wave
        double angleRadians = angleDegrees * (M_PI / 180.0);
        double cubeHeight = ((std::sin(angleRadians) + 1) / 2) + 2.0;

        // Drawing
        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        BeginMode3D(camera); // Begin 3D mode

        // Draw a solid cube (Position, Width, Height, Length, Color)
        DrawCube((Vector3){0.0, 0.0, 0.0}, 2.0, cubeHeight, 2.0, RED);
        // Draw the cube's wireframe outline on top
        DrawCubeWires((Vector3){0.0, 0.0, 0.0}, 2.0, cubeHeight, 2.0, MAROON);

        // Draw a reference grid on the ground
        // DrawGrid(10, 1.0f);

        EndMode3D(); // End 3D mode

        DrawFPS(10, 10); // Put FPS on screen

        EndDrawing(); // End drawing
    }
    CloseWindow(); // Must close window

    return 0;
}