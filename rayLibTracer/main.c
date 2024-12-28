#include "raylib/src/raylib.h"
#include <math.h>

/* Let's start with our basic structures
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
    const int screenWidth = 800;
    const int screenHeight = 600;
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

    SetTargetFPS(60);

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
}*/

typedef struct {
    Vector3 origin;
    Vector3 direction;
} _Ray;

typedef struct {
    Vector3 center;
    float radius;
    Color color;
} Sphere;

// Helper function to create normalized vector
Vector3 normalize_vector(Vector3 v) {
    float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector3){v.x/len, v.y/len, v.z/len};
}

// Ray-Sphere intersection (the math you're familiar with!)
float intersect_sphere(_Ray ray, Sphere sphere) {
    Vector3 oc = {
        ray.origin.x - sphere.center.x,
        ray.origin.y - sphere.center.y,
        ray.origin.z - sphere.center.z
    };

    float a = ray.direction.x * ray.direction.x +
              ray.direction.y * ray.direction.y +
              ray.direction.z * ray.direction.z;

    float b = 2.0f * (oc.x * ray.direction.x +
                      oc.y * ray.direction.y +
                      oc.z * ray.direction.z);

    float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z -
              sphere.radius * sphere.radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) return -1.0f;

    return (-b - sqrt(discriminant)) / (2.0f*a);
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Real Raytracer");

    // Create an image we can draw pixels to
    Image image = GenImageColor(screenWidth, screenHeight, BLACK);
    Texture2D texture = LoadTextureFromImage(image);

    // Camera setup for ray generation
    Vector3 camera_pos = {0, 0, -5};
    float viewport_width = 2.0f;
    float viewport_height = 1.5f;
    float focal_length = 1.0f;

    // Create a test sphere
    Sphere sphere = {
        .center = {0, 0, 0},
        .radius = 1.0f,
        .color = RED
    };

    // This is where the actual raytracing happens!
    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
            // Convert pixel coordinates to viewport coordinates
            float viewport_x = (x / (float)screenWidth * viewport_width) - viewport_width/2;
            float viewport_y = ((screenHeight-y) / (float)screenHeight * viewport_height) - viewport_height/2;

            // Create ray from camera through this pixel
            _Ray ray = {
                .origin = camera_pos,
                .direction = normalize_vector((Vector3){
                    viewport_x,
                    viewport_y,
                    focal_length
                })
            };

            // Check for intersection
            float t = intersect_sphere(ray, sphere);

            // If we hit something, color the pixel
            if (t > 0) {
                ImageDrawPixel(&image, x, y, sphere.color);
            }
        }
    }

    // Update texture with our raytraced image
    UpdateTexture(texture, image.data);

    while (!WindowShouldClose()) {
        BeginDrawing();
            DrawTexture(texture, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadImage(image);
    CloseWindow();
    return 0;
}
