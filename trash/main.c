#include "cub3d.h"


void fill_map(t_data *data, char *str)
{
    int fd;
    fd = open(str, O_RDONLY);
    data->map = malloc(sizeof(char *) * 7);
    data->map[0] = get_next_line(3);

    data->map[1] = get_next_line(3);
    data->map[2] = get_next_line(3);
    data->map[3] = get_next_line(3);
    data->map[4] = get_next_line(3);
    data->map[5] = get_next_line(3);
    data->map[6] = get_next_line(3);

    int f0 = 90;
    int f1 = 0;
    int f2 = 22;

    int c0 = 20;
    int c1 = 105;
    int c2 = 100;

    data->floor_color = (f0 << 16) + (f1 << 8) + f2;
    data->ceiling_color = (c0 << 16) + (c1 << 8) + c2;

}

void player_location(t_data *data)
{
    int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->locx = i;
				data->locy = j;
				data->player_dir = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void ft_cam(t_data *data)
{
    if(data->map[data->locx][data->locy] == 'N')
    {
        data->dirx = -1;
        data->diry = 0;
        data->planex = 0;
        data->planey = -0.66;
    }

    else if(data->map[data->locx][data->locy] == 'S')
    {
        data->dirx = 1;
        data->diry = 0;
        data->planex = 0;
        data->planey = 0.66;
    }
    else if(data->map[data->locx][data->locy] == 'W')
    {
        data->dirx = 0;
        data->diry = -1;
        data->planex = -0.66;
        data->planey = 0;
    }
    else if(data->map[data->locx][data->locy] == 'E')
    {
        data->dirx = 0;
        data->diry = 1;
        data->planex = 0.66;
        data->planey = 0;
    }
}

void destroy_win(t_data *data)
{
    mlx_destroy_image(data->mlx_in, data->mlx_obj);
    data->mlx_obj = mlx_new_image(data->mlx_in, 1920, 1080);
    data->mlx_info = (int *)mlx_get_data_addr(data->mlx_obj, &data->bits, &data->bits, &data->endi);

}

void ft_floor(t_data *data)
{
    int	x;
	int	y;

	x = -1;

	while (++x < data->map_width)
	{
		y = -1;
		while (++y < data->map_height)
		{
			if (y < data->map_height / 2)
			    data->mlx_info[y * data->map_width
					+ x] = data->ceiling_color;
			else
				data->mlx_info[y * data->map_width
					+ x] = data->floor_color;
		}
	}

}
void	ft_raycasting(t_data *data)
{
	int	x;

	x = 0;

	while (x < data->map_width)
	{
		data->camerax = 2 * x / (double)1920 - 1;
		data->raydirx = data->dirx + data->planex * data->camerax;
        data->raydiry = data->diry + data->planey * data->camerax;
		data->mapx = (int)data->locx;
		data->mapy = (int)data->locy;
		data->deltadistx = fabs(1 / data->raydirx);
		data->deltadisty = fabs(1 / data->raydiry);
		direction(data);
		wallhit(data);
		raydist(data);
		//texture(data, x);
		x++;
	}
}

int ft_draw(t_data *data)
{
    //destroy_win(data);

    ft_floor(data);
    ft_raycasting(data);
    mlx_put_image_to_window(data->mlx_in, data->mlx_w, data->mlx_obj, 0, 0);
    return (0);
}

void	direction(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->locx - data->mapx)
			* data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->locx)
			* data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->locy - data->mapy)
			* data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->locy)
			* data->deltadisty;
	}
}

void	wallhit(t_data *data)
{
	data->wall = 0;
	while (!data->wall)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->map[data->mapx][data->mapy] == '1')
			data->wall = 1;
	}
}

void	raydist(t_data *data)
{
	if (data->side == 0)
		data->perpwalldist = data->sidedistx - data->deltadistx;
	else
		data->perpwalldist = data->sidedisty - data->deltadisty;
	data->lineheight = (int)(1080 / data->perpwalldist);
	data->drawstart = -data->lineheight / 2 + 1080 / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + 1080 / 2;
	if (data->drawend >= 1080)
		data->drawend = 1080 - 1;
}

void	set_value(t_data *data)
{
	double	wallx;

	data->texnum = data->map[data->mapx][data->mapy] - 1;
	if (data->side == 0)
		wallx = data->locy + data->perpwalldist * data->raydiry;
	else
		wallx = data->locx + data->perpwalldist * data->raydirx;
	wallx -= floor(wallx);
	data->tex_x = (int)(wallx * (double)64);
	if (data->side == 0 && data->raydirx > 0)
		data->tex_x = 64 - data->tex_x - 1;
	if (data->side == 1 && data->raydiry < 0)
		data->tex_x = 64 - data->tex_x - 1;
	data->texstep = 1.0 * 64 / data->lineheight;
	data->texpos = (data->drawstart - 1080 / 2 + data->lineheight
			/ 2) * data->texstep;
}
void	texture(t_data *data, int x)
{
	int	texy;
	set_value(data);
	printf("side %d\n",data->side);
	printf("data->raydiry %f\n",data->raydiry );
	printf("data->raydirx %f\n",data->raydirx );
	while (data->drawstart < data->drawend )
	{
	 	texy = (int)data->texpos & 63;
	 	data->texpos += data->texstep;

	 	if (data->side == 0 && data->raydirx > 0)
	     {
	 		data->mlx_obj[data->drawstart * 1920
	 			+ x] = data->so_data[64 * texy + data->tex_x];
			printf("de: \n");

	     }
	 	else if (data->side == 0 && data->raydirx < 0)
	     {
	 		data->mlx_obj[data->drawstart * 1920
	 			+ x] = data->no_data[64 * texy + data->tex_x];
			printf("de: \n");
			

	     }
	 	else if (data->side == 1 && data->raydiry > 0)
	     {
	 		data->mlx_obj[data->drawstart * 1920
	 			+ x] = data->ea_data[64 * texy + data->tex_x];
        
	     }
	 	else
	     {
	 		data->mlx_obj[data->drawstart * 1920 + x] = data->we_data[64 * texy + data->tex_x];
	     }
	 	data->drawstart++;
	 }
}


void img(t_data *data)
{
    int	x;
	int	y;

	x = 64;
	y = 64;
	data->no = mlx_xpm_file_to_image(data->mlx_in, "img/color1.xpm",
			&x, &y);
	data->no_data = (int *)mlx_get_data_addr(data->no,
			&data->no_bpp, &data->no_size_line,
			&data->no_endian);
	data->we = mlx_xpm_file_to_image(data->mlx_in, "img/color2.xpm",
			&x, &y);
	data->we_data = (int *)mlx_get_data_addr(data->we,
			&data->we_bpp, &data->we_size_line,
			&data->we_endian);
	data->so = mlx_xpm_file_to_image(data->mlx_in, "img/color2.xpm",
			&x, &y);
	data->so_data = (int *)mlx_get_data_addr(data->so,
			&data->so_bpp, &data->so_size_line,
			&data->so_endian);
	data->ea = mlx_xpm_file_to_image(data->mlx_in, "img/color2.xpm",
			&x, &y);
	data->ea_data = (int *)mlx_get_data_addr(data->ea,
			&data->ea_bpp, &data->ea_size_line,
			&data->ea_endian);
}
void ft_start(t_data *data)
{

    data->mlx_in = mlx_init();
    data->mlx_w = mlx_new_window(data->mlx_in, 1920, 1080, "CUB3D");
    data->mlx_obj = mlx_new_image(data->mlx_in, 1920, 1080);
    data->mlx_info = (int *)mlx_get_data_addr(data->mlx_obj, &data->bits, &data->bits, &data->endi);
    data->map_width = 1920;
    data->map_height = 1080;
    img(data);
    player_location(data);
    ft_cam(data);
    mlx_loop_hook(data->mlx_in, &ft_draw, data);
    mlx_loop(data->mlx_in);
}

int main(int ac, char **av)
{
    (void)ac; 
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    fill_map(data, av[1]);
    ft_start(data);
}