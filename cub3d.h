#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include "gnl/get_next_line.h"

#include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
typedef struct s_data
{
    void *mlx_in;
    void *mlx_w;
    int *mlx_obj;
    int *mlx_info;
    int bits;
    int lines;
    int endi;


    int map_width;
    int map_height;
    char **map;
    long floor_color;
    long ceiling_color;

    char player_dir;
    int locx;
    int locy;

    double dirx;
    double diry;
    double planex;
    double planey;



}t_data;

#endif