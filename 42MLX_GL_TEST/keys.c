# include "header.h"

// ESC Key pressed, program should exit
void keyCheck(mlx_key_data_t keydata, void *param)
{
    mlx_t* mlx = (mlx_t *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        printf("ESC key pressed\n");
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
        mlx_close_window(mlx);
}

