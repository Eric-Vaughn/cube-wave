#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <raylib.h>

const unsigned int FPS = 60;
const unsigned int NUM_ROWS = 9;                 // Odd for center
const unsigned int NUM_COLS = NUM_ROWS;          // Cube
const unsigned int CUBE_POS_OFFSET = 2;          // Testing buffer b/w cubes
const double ANIMATION_SPEED_MULTIPLIER = 180.0; // Speed in degrees per second (180°/sec = full rotation in 2 seconds)

// Helper to get the current time in seconds
double getTimeInSeconds()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration<double>(duration).count();
}

// Helper that converts degrees to radians
double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

// Helper that mutates the given angle based on time elapsed
double updateValueDegrees(double oscillatingValueDegrees, const double deltaTime, double degreesPerSecond = ANIMATION_SPEED_MULTIPLIER)
{
    oscillatingValueDegrees += degreesPerSecond * deltaTime; // Does NOT mutates given angle

    // Wrap around 360 degrees (no precsision loss)
    if (oscillatingValueDegrees >= 360.0)
    {
        oscillatingValueDegrees = 0.0; // Reset the given angle (no mutating)
    }

    return oscillatingValueDegrees;
}

// Helper that calculates what height a cube should be
double calculateCubeHeight(const double pos, const double oscillatingValueDegrees)
{
    const double SCALAR = 20;
    const double MIN_HEIGHT = 2.0;
    /*
        sin(radianAngle)    --> -1.0...1.0      --> SINE'S RANGE
        + 1                 --> 0.0...2.0       --> ZERO OUT LOWER BOUND
        / 2                 --> 0.0...1.0       --> NORMALIZE
        * SCALAR            --> 0.0...SCALAR    --> SCALE
        + MIN        --> MIN...SCALAR + MIN     --> SHIFT BY MIN
    */
    return (((std::sin(degreesToRadians(oscillatingValueDegrees + pos)) + 1) / 2) * SCALAR) + MIN_HEIGHT;
}

int main()
{
    InitWindow(800, 800, "Cube Wave"); // Create window
    SetTargetFPS(FPS);

    // Create a 3D camera
    Camera3D camera = {0};
    camera.position = (Vector3){30.0f, 30.0f, 30.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector
    camera.fovy = 100.0f;                             // Field of view (in orthographic mode, fovy acts as the view size/zoom width)
    camera.projection = CAMERA_ORTHOGRAPHIC;          // Projection type

    double oscillatingValueDegrees = 0.0; // Initial value
    double lastTime = getTimeInSeconds(); // Initial time

    // Create & generate a vector of cube position
    std::vector<Vector3> cubePosArray = {};

    for (int i = 0; i < NUM_ROWS; i++)
    {
        double xOffset = i * CUBE_POS_OFFSET;

        for (int j = 0; j < NUM_COLS; j++)
        {
            double yOffset = j * CUBE_POS_OFFSET;
            cubePosArray.push_back((Vector3){(float)i + (float)xOffset, 0, (float)j + (float)yOffset});
        }
    }

    // Main game loop
    while (!WindowShouldClose())
    {
        // Moving the cube up and down
        double currentTime = getTimeInSeconds();   // Get/Update current time
        double deltaTime = currentTime - lastTime; // Calculate Delta Time (seconds passed since the previous frame)
        lastTime = currentTime;                    // Update previous time

        // -------------
        // -- Drawing --
        // -------------

        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        BeginMode3D(camera); // Begin 3D mode

        // Draw a solid cube (Position, Width, Height, Length, Color)
        // DrawCube((Vector3){0.0, 0.0, 0.0}, 2.0, cubeHeight, 2.0, RED);
        // Draw the cube's wireframe outline on top
        // DrawCubeWires((Vector3){0.0, 0.0, 0.0}, 2.0, cubeHeight, 2.0, MAROON);

        // Increase value based on time passed, not frame rate
        oscillatingValueDegrees = updateValueDegrees(oscillatingValueDegrees, deltaTime);

        // Draw all the cubes
        for (Vector3 cubePos : cubePosArray)
        {

            // Get cube height
            double cubeHeight = calculateCubeHeight(cubePos.x, oscillatingValueDegrees);

            DrawCube(cubePos, 2.0, cubeHeight, 2.0, RED);
            DrawCubeWires(cubePos, 2.0, cubeHeight, 2.0, MAROON);
        }

        // Draw a reference grid on the ground
        // DrawGrid(10, 1.0f);

        EndMode3D(); // End 3D mode

        DrawFPS(10, 10); // Put FPS on screen

        EndDrawing(); // End drawing
    }

    CloseWindow(); // Must close window

    return 0;
}