#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include "gnl/get_next_line.h"

#include <stdio.h>
# include <fcntl.h>
#include <math.h>
# include <stdlib.h>
#include <string.h>
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
    double camerax;
    double raydirx;
    double raydiry;
    double deltadistx;
    double deltadisty;
    double sidedistx;
    double sidedisty;
	double	perpwalldist;
    int	mapx;
	int	mapy;
    int	stepx;
	int	stepy;
	int	wall;
    int side;
	int	lineheight;
	int	drawstart;
	int drawend;
    double	texstep;
	double	texpos;
	int	texnum;
	int	tex_x;


	char		*ea1;
	char		*so1;
	char		*we1;
	char		*no1;

    int			size;
	void		*no;
	int			*no_data;
	int			no_bpp;
	int			no_size_line;
	int			no_endian;

	int			*so_data;
	int			so_bpp;
	int			so_size_line;
	int			so_endian;

	int			*we_data;
	int			we_bpp;
	int			we_size_line;
	int			we_endian;

	int			*ea_data;
	int			ea_bpp;
	int			ea_size_line;
	int			ea_endian;

	void		*so;
	void		*we;
	void		*ea;
}t_data;

void player_location(t_data *data);
void ft_cam(t_data *data);
void destroy_win(t_data *data);
void ft_floor(t_data *data);
void	ft_raycasting(t_data *data);
int ft_draw(t_data *data);
void	direction(t_data *data);
void	wallhit(t_data *data);
void	raydist(t_data *data);
void	set_value(t_data *data);
void	texture(t_data *data, int x);
void img(t_data *data);
void ft_start(t_data *data);

#endif