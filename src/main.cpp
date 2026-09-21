#include <string>
#include <cmath>
#include <chrono>
#include <raylib.h>

const unsigned int FPS = 60;
const double ANIMATION_SPEED_MULTIPLIER = 180.0; // Speed in degrees per second (180°/sec = full rotation in 2 seconds)

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

// Helper that mutates the given angle based on time elapsed
void updateAngleDegrees(double &angleDegrees, const double deltaTime, double degreesPerSecond = ANIMATION_SPEED_MULTIPLIER)
{
    angleDegrees += degreesPerSecond * deltaTime; // Mutates given angle

    // Wrap around 360 degrees (no precsision loss)
    if (angleDegrees >= 360.0)
    {
        angleDegrees = 0.0; // Reset the given angle
    }
}

// Helper that calculates what height a cube should be
double calculateCubeHeight(double angleDegrees)
{
    const double SCALAR = 20;
    const double MIN_HEIGHT = 2.0;
    /*
        sin(radianAngle)    --> -1.0...1.0
        + 1                 --> 0.0...2.0
        / 2                 --> 0.0...1.0 --> NORMALIZED
        * SCALAR            --> 0.0...SCALAR
        + MIN_HEIGHT        --> MIN_HEIGHT...SCALAR + MIN_HEIGHT
    */
    return (((std::sin(degreesToRadians(angleDegrees)) + 1) / 2) * SCALAR) + MIN_HEIGHT;
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

    // Control
    double angleDegrees = 0.0;
    double lastTime = getTimeInSeconds(); // Get initial time

    // Main game loop
    while (!WindowShouldClose())
    {
        // Moving the cube up and down
        double currentTime = getTimeInSeconds();   // Get current time
        double deltaTime = currentTime - lastTime; // Calculate Delta Time (seconds passed since the last frame)
        lastTime = currentTime;                    // Update previous time

        // Increase angle based on time passed, not frame rate
        updateAngleDegrees(angleDegrees, deltaTime);

        // Get cube height
        double cubeHeight = calculateCubeHeight(angleDegrees);

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