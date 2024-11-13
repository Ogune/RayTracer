#include "header.h"

void ft_background(mlx_image_t *image, uint32_t color)
{
    printf("Setting background color: 0x%08X\n", color);
    for (uint32_t y = 0; y < image->height; y++)
    {
        for (uint32_t x = 0; x < image->width; x++)
        {
            mlx_put_pixel(image, x, y, color);
        }
    }
}
