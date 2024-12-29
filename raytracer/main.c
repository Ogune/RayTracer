/* -- main.c -- */
/* "What color should each pixel of the image be?" */

#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <math.h>

/* Global variables */
const int screenWidth = 400;
const int screenHeight = 300;
float aspect_ratio = (float)screenWidth / (float)screenHeight;

/* Sphere struct */
typedef struct {
	Vector3 center;
	float radius;
	Color color;
} Sphere;

typedef struct {
	Vector3 point;
	Vector3 normal;
	Color color;
} Plane;

Ray GetRayFromPixel(Vector3 camera_pos, int x, int  y) {
	float normalized_x = (2.0f * x / screenWidth) - 1.0f;
	float normalized_y = 1.0f - (2.0f * y / screenHeight);

	/* Hadi: adjust aspect ratio */
	normalized_x *= aspect_ratio;

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
	/* Mathematically: a = D ⋅ D */
	float a = Vector3DotProduct(ray.direction, ray.direction);

	/* Mathematically: b = 2 ⋅(D ⋅oc) */
	float b = 2.0f * Vector3DotProduct(oc, ray.direction);
	
	/* Mathematically: c = (oc ⋅oc) − r * r */
	float c = Vector3DotProduct(oc, oc) - powf(sphere.radius, 2);

	/* Mathematically: Δ = pow(b, 2) - 4ac */
	float Δ = pow(b, 2) - 4 * a * c;

	/* if Δ < 0; there is no solution of this equation */
	if (Δ < 0) return 0;

	/* if (Δ >= 0); there is 1 to 2 solutions, but we don't really */
	*distance = (-b - sqrt(Δ)) / (2.0f * a);
	return *distance > 0;
}

bool RayPlaneIntersect(Ray ray, Plane plane, float* distance){
	float denom = Vector3DotProduct(plane.normal, ray.direction);

	if (denom <= 0.0001) return false;
	
	Vector3 p0_minus_o = Vector3Subtract(plane.point, ray.position);

	/* Calculate t = (n⋅(P₀ - O)) / (n⋅D) */
	*distance = Vector3DotProduct(plane.normal, p0_minus_o) / denom;
	return *distance > 0;
}

int main(void) {
	InitWindow(screenWidth, screenHeight, "Ray Tracer");

	RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

	Sphere sphere = {
		.center = (Vector3){0.0f, 0.0f, 0.0f},
		.radius = 1.0f,
		.color = RED
	};
	Plane plane = {
		.point = (Vector3){0.0f, 0.0f, 0.0f},
		.normal = (Vector3){0, 1, 0},
		.color = SKYBLUE
	};
	Vector3 camera_pos = {0.0f, 0.0f, -5.0f};
	Vector3 light_pos = {5.0f, 5.0f, -5.0f}; // Position of the light source

	SetTargetFPS(90);

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_W)) camera_pos.z += 0.1f;
		if (IsKeyDown(KEY_S)) camera_pos.z -= 0.1f;
		if (IsKeyDown(KEY_A)) camera_pos.x -= 0.1f;
		if (IsKeyDown(KEY_D)) camera_pos.x += 0.1f;

		BeginTextureMode(target);
		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				Ray ray = GetRayFromPixel(camera_pos, x, y);
				float distance;
				/*if (RaySphereIntersect(ray, sphere, &distance)) {
                    Vector3 point = Vector3Add(ray.position, Vector3Scale(ray.direction, distance));
                    Vector3 normal = Vector3Normalize(Vector3Subtract(point, sphere.center));
                    Vector3 light_dir = Vector3Normalize(Vector3Subtract(light_pos, point));
                    float intensity = fmax(Vector3DotProduct(normal, light_dir), 0.0f);
                    //Color shaded_color = Fade(sphere.color, intensity); // Scale color by intensity
					Color shaded_color = {
        				.r = fmin(sphere.color.r * intensity, 255),
        				.g = fmin(sphere.color.g * intensity, 255),
      					.b = fmin(sphere.color.b * intensity, 255),
        				.a = sphere.color.a
   					 };
					DrawPixel(x, y, shaded_color);
				}*/
				if (RayPlaneIntersect(ray, plane, &distance)) {
					DrawPixel(x, y, plane.color);
				}
				/*else
					DrawPixel(x, y, BLACK); */
			}
		}
		EndTextureMode();

		BeginDrawing();
			ClearBackground(BLACK); DrawTextureRec(target.texture,
							(Rectangle){0, 0, target.texture.width, -target.texture.height},
							(Vector2){0, 0}, 
							WHITE);
			DrawFPS(10, 10);
		EndDrawing();
	}
	UnloadRenderTexture(target);
	CloseWindow();
}
