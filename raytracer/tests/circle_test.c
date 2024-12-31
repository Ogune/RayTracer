#include "../raylib/src/raylib.h"

int main(void) {
    // Create a window
    InitWindow(800, 600, "Circle Example");
    
    // Define circle properties
    Vector3 center = { 0.0f, 0.0f, 0.0f };  // Center of circle
    float radius = 2.0f;                     // Size of circle
    
    // Create a camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 0.0f, -10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Looking at center
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Up direction
    camera.fovy = 45.0f;                               // Field of view
    camera.projection = CAMERA_PERSPECTIVE;            // 3D view

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode3D(camera);
                // Draw circle outline
                DrawCircle3D(center, radius, 
                            (Vector3){1,0,0},  // This makes circle face right
                            0.0f,              // Rotation
                            RED);
            EndMode3D();
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
