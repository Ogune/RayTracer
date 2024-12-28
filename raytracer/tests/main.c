#include "../raylib/src/raylib.h"
#include <math.h>

// Let's start with our basic structures
typedef struct {
    Vector3 center;    // raylib provides Vector3!
    float radius;
    Color color;      // raylib provides Color too!
} Sphere;

typedef struct {
    Vector3 position;
    Vector3 normal;
    Color color;
} Plane;

typedef struct {
    Vector3 position;
    Vector3 direction;
    float radius;
    float height;
    Color color;
} Cylinder;

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "RayLib RayTracer");

    // Create a camera for 3D (raylib makes this easy!)
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};  // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};         // Camera up vector
    camera.fovy = 45.0f;                              // Field of view
    camera.projection = CAMERA_PERSPECTIVE;            // Perspective mode

    // Example objects
    Sphere sphere = {
        .center = (Vector3){0, 0, 0},
        .radius = 2.0f,
        .color = RED
    };

    Plane plane = {
        .position = (Vector3){0, -2, 0},
        .normal = (Vector3){0, 1, 0},
        .color = GREEN
    };

    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        // Update camera controls (mouse/keyboard)
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                // Draw sphere
                DrawSphere(sphere.center, sphere.radius, sphere.color);

                // Draw plane as a large rectangle
                DrawPlane((Vector3){0, -2, 0}, (Vector2){20, 20}, GREEN);

            EndMode3D();

            // Draw UI info
            DrawFPS(10, 10);
            DrawText("Move camera with mouse and WASD keys", 10, 30, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
