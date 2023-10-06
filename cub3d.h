#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"

typedef struct s_data
{
    void *mlx_in;
    void *mlx_w;
    void *mlx_obj;
    int *mlx_info;
    int bits;
    int lines;
    int endi;


    int map_width;
    int map_height;
    char **map;
}t_data;

#endif