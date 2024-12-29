#include "header.h"

// Image struct to store the image data
mlx_image_t* image;

int32_t main(void)
{
    mlx_t* mlx = mlx_init(W_W, W_H, "rayTracer", false);
    if (!mlx) return (EXIT_FAILURE);

    image = mlx_new_image(mlx, W_W, W_H);
    if (!image) return (EXIT_FAILURE);

    // Create a red color (1.0, 0.0, 0.0, 1.0)
    uint32_t color = createColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Set the background
    ft_background(image, color);

    // Put the image to the window
    mlx_image_to_window(mlx, image, 0, 0);

    mlx_key_hook(mlx, &keyCheck, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}
