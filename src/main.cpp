#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <raylib.h>

const unsigned int FPS = 60;
const unsigned int NUM_ROWS = 21;       // Keep value odd for center
const unsigned int NUM_COLS = NUM_ROWS; // Cube of cubes, so cols = rows
// Half --> floor --> + 1
// || 9 / 2 = 4.5 --> floor(4.5) = 4.0 --> 4 + 1 = 5
// || XXXX(X)XXXX
const unsigned int MID_OF_NUM_ROWS = (unsigned int)(std::floor((float)(NUM_ROWS) / 2)) + 1;
const unsigned int MID_OF_NUM_COLS = (unsigned int)(std::floor((float)(NUM_COLS) / 2)) + 1;
const double CUBE_SIZE = 1.0; // Base length, width, height

// Helper that converts degrees to radians
double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

// Helper to map a double's value's range to a new range
double mapDoubleToDouble(
    const double val,
    const double old_min,
    const double old_max,
    const double new_min,
    const double new_max)
{
    // Formula
    return new_min + ((val - old_min) * (new_max - new_min)) / (old_max - old_min);
}

// Helper that calculates what height a cube should be
double calculateCubeHeight(const Vector3 pos, const double oscillatingAngleDegrees)
{
    // Calculate distance from center to create the circular wave pattern
    float distance = sqrtf(pos.x * pos.x + pos.z * pos.z);

    // Map the distance and angle into a sine wave to determine dynamic height
    // The multiplier inside sine adjusts the frequency of the ripple
    float offset = distance * 0.4f;
    float height = mapDoubleToDouble(sinf(oscillatingAngleDegrees - offset), -1.0, 1.0, 1.0, 6.0);

    return height;
}

// Helper to generate a vector of cube position
std::vector<Vector3> genVecOfCubePositions()
{
    std::vector<Vector3> cubePosArray = {};

    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            // Calculate centered coordinates so the grid centers at (0,0,0)
            double xOffset = (i * CUBE_SIZE) - (NUM_ROWS * CUBE_SIZE / 2.0) + (CUBE_SIZE / 2.0);
            double yOffset = (j * CUBE_SIZE) - (NUM_ROWS * CUBE_SIZE / 2.0) + (CUBE_SIZE / 2.0);
            cubePosArray.push_back((Vector3){(float)i + (float)xOffset, 0, (float)j + (float)yOffset});
        }
    }

    return cubePosArray;
}

int main()
{
    InitWindow(800, 800, "Cube Wave"); // Create window
    SetTargetFPS(FPS);

    // Create a 3D camera
    Camera3D camera = {0};
    camera.position = (Vector3){60.0f, 60.0f, 60.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector
    camera.fovy = 80.0f;                              // Field of view (in orthographic mode, fovy acts as the view size/zoom width)
    camera.projection = CAMERA_ORTHOGRAPHIC;          // Projection type

    double oscillatingAngleDegrees = 0.0; // Initial value

    // Create a vector for cube posisitons
    std::vector<Vector3> cubePosArray = genVecOfCubePositions();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update angle
        oscillatingAngleDegrees += 0.05;

        if (oscillatingAngleDegrees >= 360.0)
            oscillatingAngleDegrees = 0.0;

        // -------------
        // -- Drawing --
        // -------------

        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        BeginMode3D(camera); // Begin 3D mode

        // Draw all the cubes
        for (Vector3 cubePos : cubePosArray)
        {

            // Get cube height
            double cubeHeight = calculateCubeHeight(cubePos, oscillatingAngleDegrees);

            DrawCube(cubePos, CUBE_SIZE, cubeHeight, CUBE_SIZE, RED);
            DrawCubeWires(cubePos, CUBE_SIZE, cubeHeight, CUBE_SIZE, MAROON);
        }

        EndMode3D(); // End 3D mode

        DrawFPS(10, 10); // Put FPS on screen

        EndDrawing(); // End drawing
    }

    CloseWindow(); // Must close window

    return 0;
}