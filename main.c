#include "raycast.h"

void init(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, S_W, S_H, "CUB3D");
    mlx->img = mlx_new_image(mlx->mlx, S_W, S_H);
}

int main()
{
    t_mlx mlx;

    init(&mlx);
    mlx_loop(mlx.mlx);
    return (0);
}