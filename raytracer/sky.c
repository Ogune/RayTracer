#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <math.h>
#include <stdio.h>

/* Global variables */
const int screenWidth = 800;
const int screenHeight = 600;
float aspect_ratio = (float)screenWidth / (float)screenHeight;

int main(void) {
	InitWindow(screenWidth, screenHeight, "Skydome");
	Image stars = LoadImage("stars.png");
	Texture2D startTxt = LoadTextureFromImage(stars);
	RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
	SetTargetFPS(90);

	while (!WindowShouldClose()) {
		BeginTextureMode(target);
		for (int y = 0; y < screenHeight; y++) {
			for (int x = 0; x < screenWidth; x++) {
				/* Normalize screen cordinates */
				float u = (float)x / screenWidth;
				float v = (float)y / screenHeight;

				/* Map to texture */
				int texX = (int)(u * stars.width);
				int texY = (int)(v * stars.height);

				/* Get the color from the texture */
				Color pixelColor = GetImageColor(stars, texX, texY);

				/* Rsem lia l9lawi */
				DrawPixel(x, y, pixelColor);
			}
		}
		EndTextureMode();

		BeginDrawing();
		DrawTextureRec(target.texture,
              (Rectangle){0, 0, target.texture.width, -target.texture.height},
              (Vector2){0, 0},
              WHITE);
		DrawFPS(10,10);
		EndDrawing();
	}
	UnloadImage(stars);
	UnloadTexture(startTxt);
	UnloadRenderTexture(target);
	CloseWindow();
}
