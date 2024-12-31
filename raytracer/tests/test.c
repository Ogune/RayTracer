#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <math.h>

/* Global variables */
const int screenWidth = 600;
const int screenHeight = 400;
float aspect_ratio = (float)screenWidth / (float)screenHeight;

/* Base structures */
typedef struct {
    Vector3 center;
    float radius;
    float rotation;    // Current rotation angle
    Image image;       // Earth image data
    Texture2D texture; // Earth texture
} Earth;

/* Get color from texture at specific UV coordinates */
Color SampleTexture(Image image, float u, float v) {
    int x = (int)(u * image.width) % image.width;
    int y = (int)(v * image.height) % image.height;
    
    // Handle negative coordinates
    if (x < 0) x += image.width;
    if (y < 0) y += image.height;
    
    return GetImageColor(image, x, y);
}

/* Ray functions */
Ray GetRayFromPixel(Vector3 camera_pos, int x, int y) {
    float normalized_x = (2.0f * x / screenWidth) - 1.0f;
    float normalized_y = 1.0f - (2.0f * y / screenHeight);

    normalized_x *= aspect_ratio;

    Ray ray;
    ray.position = camera_pos;
    ray.direction = (Vector3){normalized_x, normalized_y, 1.0f};
    ray.direction = Vector3Normalize(ray.direction);

    return ray;
}

bool RaySphereIntersect(Ray ray, Vector3 center, float radius, float* distance) {
    Vector3 oc = Vector3Subtract(ray.position, center);
    
    float a = Vector3DotProduct(ray.direction, ray.direction);
    float b = 2.0f * Vector3DotProduct(oc, ray.direction);
    float c = Vector3DotProduct(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return false;

    *distance = (-b - sqrt(discriminant)) / (2.0f * a);
    return *distance > 0;
}

void get_texture_coordinates(Vector3 point, Vector3 center, float* u, float* v) {
    Vector3 normalized = Vector3Normalize(Vector3Subtract(point, center));
    
    *u = 0.5f + (atan2f(normalized.z, normalized.x) / (2.0f * PI));
    *v = 0.5f - (asinf(normalized.y) / PI);
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Earth Ray Tracer");

    // Load the texture and keep the image data
    Image earthImage = LoadImage("earth.png");
    
    Earth earth = {
        .center = {0.0f, 0.0f, 0.0f},
        .radius = 1.0f,
        .rotation = 0.0f,
        .image = earthImage,
        .texture = LoadTextureFromImage(earthImage)
    };

    Vector3 camera_pos = {0.0f, 0.0f, -5.0f};
    Vector3 light_pos = {5.0f, 5.0f, -5.0f};

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Rotate Earth
        earth.rotation += 0.004f;

        // Camera controls
        if (IsKeyDown(KEY_W)) camera_pos.z += 0.1f;
        if (IsKeyDown(KEY_S)) camera_pos.z -= 0.1f;
        if (IsKeyDown(KEY_A)) camera_pos.x -= 0.1f;
        if (IsKeyDown(KEY_D)) camera_pos.x += 0.1f;
        if (IsKeyDown(KEY_UP)) camera_pos.y += 0.1f;
        if (IsKeyDown(KEY_DOWN)) camera_pos.y -= 0.1f;

        BeginTextureMode(target);
            ClearBackground(BLACK);
            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    Ray ray = GetRayFromPixel(camera_pos, x, y);
                    float distance;

                    if (RaySphereIntersect(ray, earth.center, earth.radius, &distance)) {
                        // Calculate intersection point
                        Vector3 point = Vector3Add(ray.position, Vector3Scale(ray.direction, distance));
                        
                        // Calculate normal at intersection point
                        Vector3 normal = Vector3Normalize(Vector3Subtract(point, earth.center));
                        
                        // Get texture coordinates
                        float u, v;
                        get_texture_coordinates(point, earth.center, &u, &v);
                        
                        // Apply rotation
                        u = fmodf(u + earth.rotation, 1.0f);
                        
                        // Sample texture using our new function
                        Color color = SampleTexture(earth.image, u, v);
                        
                        // Apply lighting
                        Vector3 light_dir = Vector3Normalize(Vector3Subtract(light_pos, point));
                        float intensity = fmax(Vector3DotProduct(normal, light_dir), 0.1f);
                        
                        color.r = (unsigned char)(color.r * intensity);
                        color.g = (unsigned char)(color.g * intensity);
                        color.b = (unsigned char)(color.b * intensity);
                        
                        DrawPixel(x, y, color);
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

    UnloadImage(earth.image);
    UnloadTexture(earth.texture);
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}
