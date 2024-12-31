#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>

/* Globale Vars */
const int screenWidth = 800;
const int screenHeight = 600;
float aspect_ratio = (float)screenWidth / (float)screenHeight;

/* Equation in 2D: (x - h)² + (y - k)² = r² */
typedef struct {
	Vector3 center;
	Vector3 normal;
	float radius;
} Circle;

bool rayCircleIntersect(Ray ray, Circle circle, Vector3 hitPoint) {
	/* find where ray intersect with circle's plane */
	float denom = Vector3DotProduct(circle.normal, ray.direction);
	
	/* Ray is paralell to circle plane */
	if (fabs(denom) < 0.0001f) return false;

	/* Vector from ray origin to circle center */
	Vector3 oc = Vector3Subtract(circle.center, ray.origin);
}

int main(int ac, char *av[]) {
	/*if (ac < 2) {
		fprintf(stderr, "Usage: %s <texture li 5ass")
	}*/
	InitWindow(screenWidth,screenHeight, "Ray Circle");
}
