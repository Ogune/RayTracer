#ifndef HEADER_H
# define HEADER_H

# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include "MLX42/MLX42.h"
# include "cglm/cglm.h"

# define W_W 800
# define W_H 600

// Color manipulation function prototypes
uint32_t get_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
uint32_t get_r(uint32_t rgba);
uint32_t get_g(uint32_t rgba);
uint32_t get_b(uint32_t rgba);
uint32_t get_a(uint32_t rgba);
uint32_t createColor(float r, float g, float b, float a);

// Background setting function prototype
void ft_background(mlx_image_t *image, uint32_t color);

// ESC key check to exit program
void keyCheck(mlx_key_data_t keydata, void *param);
// Any other function prototypes you might have had

// If you were using any custom structs, you can define them here

#endif
