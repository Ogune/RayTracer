#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>

#include "../raylib/src/raylib.h"
#include <math.h>

typedef struct {
    Vector3 center;
    float radius;
    Color color;
} Sphere;

typedef struct {
    Vector3 position;
    Vector3 normal;
    Color color;
} Plane;

Ray GetRayFromPixel(Vector3 camera_pos, int x, int y, int screenWidth, int screenHeight) {
    float normalized_x = (2.0f * x / screenWidth) - 1.0f;
    float normalized_y = 1.0f - (2.0f * y / screenHeight);

    Ray ray;
    ray.position = camera_pos;
    ray.direction = (Vector3){normalized_x, normalized_y, 1.0f};
    ray.direction = Vector3Normalize(ray.direction);

    return ray;
}

bool RaySphereIntersect(Ray ray, Sphere sphere, float* distance) {
    Vector3 oc = Vector3Subtract(ray.position, sphere.center);

    float a = Vector3DotProduct(ray.direction, ray.direction);
    float b = 2.0f * Vector3DotProduct(oc, ray.direction);
    float c = Vector3DotProduct(oc, oc) - sphere.radius * sphere.radius;

    float delta = b * b - 4.0f * a * c;

    if (delta < 0.0f) return false;
    *distance = (-b - sqrtf(delta)) / (2.0f * a);

    return *distance >= 0.0f;
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "RayTracer with Camera Controls");

    // Create a camera for 3D
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 10.0f, 10.0f};  // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector
    camera.fovy = 45.0f;                               // Field of view
    camera.projection = CAMERA_PERSPECTIVE;             // Perspective mode

    // Create objects
    Sphere sphere = { .center = (Vector3){0, 0, 0}, .radius = 2.0f, .color = RED };
    Plane plane = { .position = (Vector3){0, -2, 0}, .normal = (Vector3){0, 1, 0}, .color = GREEN };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update camera controls (mouse/keyboard)
        UpdateCamera(&camera, CAMERA_FREE);  // Make sure to update the camera using the mouse and WASD

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Perform ray tracing for each pixel (this simulates the 3D scene)
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                Ray ray = GetRayFromPixel(camera.position, x, y, screenWidth, screenHeight);
                float distance;
                if (RaySphereIntersect(ray, sphere, &distance)) {
                    Color shaded_color = Fade(sphere.color, 0.5f);
                    DrawPixel(x, y, shaded_color);  // Ray-traced color on screen
                } else {
                    DrawPixel(x, y, BLACK);  // Background (no intersection)
                }
            }
        }

        // Render the 3D objects (sphere and plane)
        BeginMode3D(camera);
            // Draw sphere and plane in the scene
            DrawSphere(sphere.center, sphere.radius, sphere.color);
            DrawPlane(plane.position, (Vector2){20, 20}, plane.color);
        EndMode3D();

        // Draw FPS and information
        DrawFPS(10, 10);
        DrawText("Move camera with mouse and WASD keys", 10, 30, 20, BLACK);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

