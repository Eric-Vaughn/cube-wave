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
const unsigned int CUBE_POS_OFFSET = 2;          // Testing buffer b/w cubes
const double CUBE_SIZE = 2.0;                    // Base length, width, height
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
double updateValueDegrees(double oscillatingAngleDegrees, const double deltaTime, double degreesPerSecond = ANIMATION_SPEED_MULTIPLIER)
{
    oscillatingAngleDegrees += degreesPerSecond * deltaTime / FPS; // Does NOT mutates given angle

    // Wrap around 360 degrees (no precsision loss)
    if (oscillatingAngleDegrees >= 360.0)
    {
        oscillatingAngleDegrees = 0.0; // Reset the given angle (no mutating)
    }

    return oscillatingAngleDegrees;
}

// Helper to map a double's value's range to a new range
double mapDoubleRangeToDoubleRange(
    const double val,
    const double old_min,
    const double old_max,
    const double new_min,
    const double new_max)
{
    // Formula
    return new_min + ((val - old_min) * (new_max - new_min)) / (old_max - old_min);
}

// Helper to find the mag of a vector2d
double getMagVector2d(const double val1, const double val2)
{
    return std::sqrt(std::pow(val1, 2) + std::pow(val2, 2));
}

// Helper to get the distance between 2 vector 2Ds
double distVector2d(const Vector2 v1, const Vector2 v2)
{
    const double dx = v2.x - v1.x;
    const double dy = v2.y - v1.y;

    return std::hypot(dy, dy);
}

// TODO: Change cube height based off absolute val away from center cube (const MID_OF_NUM_ROWS)
// Helper that calculates what height a cube should be
double calculateCubeHeight(const Vector3 pos, const double oscillatingAngleDegrees)
{

    // NOTE: The pos.y of the Vector2's is the pos.z value of the Vector3's.
    // This is because we are working with the (x, z) plane.
    // const Vector2 shiftedPos = {pos.x + ((float)MID_OF_NUM_ROWS - 1) * CUBE_POS_OFFSET, pos.z + ((float)MID_OF_NUM_COLS - 1) * CUBE_POS_OFFSET};
    // const Vector2 shiftedPos = {pos.x, pos.z};
    // const Vector2 centerPos = {((double)MID_OF_NUM_ROWS - 1) * CUBE_POS_OFFSET, ((double)MID_OF_NUM_COLS - 1) * CUBE_POS_OFFSET};

    // // const Vector3 testVecShift = {shiftedPos.x, 10.0, shiftedPos.y};
    // // const Vector3 testVecCenter = {centerPos.x, 10.0, centerPos.y};
    // // DrawCube(testVecCenter, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, GREEN);

    // const double MAX_HEIGHT = 20.0;
    // const double MIN_HEIGHT = CUBE_SIZE;

    // const double distFromCenter = distVector2d(shiftedPos, centerPos);
    // const double MAX_DIST = std::hypot(((double)MID_OF_NUM_ROWS - 1) * CUBE_POS_OFFSET, ((double)MID_OF_NUM_COLS - 1) * CUBE_POS_OFFSET);

    // // const double offset = mapDoubleRangeToDoubleRange(distFromCenter, 0, MAX_DIST, -PI, PI);
    // const double offset = distFromCenter * 3.0;

    // const double angle = oscillatingAngleDegrees - offset;

    // const double height = mapDoubleRangeToDoubleRange(std::sin(angle), -1, 1, MIN_HEIGHT, MAX_HEIGHT);

    // return height;
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
    camera.fovy = 120.0f;                             // Field of view (in orthographic mode, fovy acts as the view size/zoom width)
    camera.projection = CAMERA_ORTHOGRAPHIC;          // Projection type

    double oscillatingAngleDegrees = 0.0; // Initial value
    double lastTime = getTimeInSeconds(); // Initial time

    // Create a vector for cube posisitons
    std::vector<Vector3> cubePosArray = genVecOfCubePositions();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Moving the cube up and down
        double currentTime = getTimeInSeconds();   // Get/Update current time
        double deltaTime = currentTime - lastTime; // Calculate Delta Time (seconds passed since the previous frame)
        lastTime = currentTime;                    // Update previous time

        oscillatingAngleDegrees += 0.05;

        if (oscillatingAngleDegrees >= 360.0)
            oscillatingAngleDegrees = 0.0;

        // -------------
        // -- Drawing --
        // -------------

        BeginDrawing();         // Create canvas to draw on
        ClearBackground(BLACK); // Clear canvas before anything else

        BeginMode3D(camera); // Begin 3D mode

        // Increase value based on time passed, not frame rate
        // oscillatingAngleDegrees = updateValueDegrees(oscillatingAngleDegrees, deltaTime);

        // Draw all the cubes
        for (Vector3 cubePos : cubePosArray)
        {

            // Get cube height
            double cubeHeight = calculateCubeHeight(cubePos, oscillatingAngleDegrees);

            DrawCube(cubePos, CUBE_SIZE, cubeHeight, CUBE_SIZE, RED);
            DrawCubeWires(cubePos, CUBE_SIZE, cubeHeight, CUBE_SIZE, MAROON);
        }

        DrawCube({0.0, 5.0, 0.0}, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, BLUE);

        // Draw a reference grid on the ground
        // DrawGrid(10, 1.0f);

        EndMode3D(); // End 3D mode

        DrawFPS(10, 10); // Put FPS on screen

        EndDrawing(); // End drawing
    }

    CloseWindow(); // Must close window

    return 0;
}