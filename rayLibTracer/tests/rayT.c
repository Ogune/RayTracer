#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>

typedef struct {
    Vector3 center;
    float radius;
    Color color;
} Sphere;

Ray GetRayFromPixel(Vector3 camera_pos, int x, int y, int width, int height) {
    float normalized_x = (2.0f * x / width) - 1.0f;
    float normalized_y = 1.0f - (2.0f * y / height);

    Ray ray;
    ray.position = camera_pos;
    ray.direction = (Vector3){normalized_x, normalized_y, 1.0f};
    ray.direction = Vector3Normalize(ray.direction);

    return ray;
}

bool RaySphereIntersect(Ray ray, Sphere sphere, float* distance) {
    Vector3 oc = {
        ray.position.x - sphere.center.x,
        ray.position.y - sphere.center.y,
        ray.position.z - sphere.center.z
    };

    float a = ray.direction.x * ray.direction.x +
              ray.direction.y * ray.direction.y +
              ray.direction.z * ray.direction.z;

    float b = 2.0f * (oc.x * ray.direction.x +
                      oc.y * ray.direction.y +
                      oc.z * ray.direction.z);

    float c = oc.x * oc.x +
              oc.y * oc.y +
              oc.z * oc.z -
              sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return false;

    *distance = (-b - sqrt(discriminant)) / (2.0f * a);
    return *distance > 0;
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "makrehtch nkemlou");

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    Sphere sphere = {
        .center = (Vector3){0.0f, 0.0f, 5.0f},
        .radius = 1.0f,
        .color = RED
    };

    Vector3 camera_pos = {0.0f, 0.0f, 0.0f};

    SetTargetFPS(90);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) camera_pos.z += 0.1f;
        if (IsKeyDown(KEY_S)) camera_pos.z -= 0.1f;
        if (IsKeyDown(KEY_A)) camera_pos.x -= 0.1f;
        if (IsKeyDown(KEY_D)) camera_pos.x += 0.1f;

        BeginTextureMode(target);
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                Ray ray = GetRayFromPixel(camera_pos, x, y, screenWidth, screenHeight);
                float distance;

                if (RaySphereIntersect(ray, sphere, &distance)) {
                    DrawPixel(x, y, sphere.color);
                } else {
                    DrawPixel(x, y, BLACK);
                }
            }
        }
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureRec(target.texture,
                (Rectangle){0, 0, target.texture.width, -target.texture.height},
                (Vector2){0, 0},
                WHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}
