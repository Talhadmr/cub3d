#include "cub3d.h"
void fill_map(t_data *data, char *str)
{
    int fd;
    printf("deb1\n");
    fd = open(str, O_RDONLY);
    data->map[0] = get_next_line(3);

    data->map[1] = get_next_line(3);
    data->map[2] = get_next_line(3);
    data->map[3] = get_next_line(3);
    data->map[4] = get_next_line(3);
    data->map[5] = get_next_line(3);
    data->map[6] = get_next_line(3);

     int f0 = 220;
    int f1 = 111;
    int f2 = 0;

    int c0 = 225;
    int c1 = 111;
    int c2 = 0;

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
			    data->mlx_obj[y * data->map_width
					+ x] = data->ceiling_color;
			else
				data->mlx_obj[y * data->map_width
					+ x] = data->floor_color;
		}
	}
}
int ft_draw(t_data *data)
{
    destroy_win(data);
    ft_floor(data);
    return (0);
}

void ft_start(t_data *data)
{

    printf("deb1\n");
    data->mlx_in = mlx_init();
    printf("deb2\n");

    data->mlx_w = mlx_new_window(data->mlx_in, 1920, 1080, "CUB3D");
    data->mlx_obj = mlx_new_image(data->mlx_in, 1920, 1080);
    data->mlx_info = (int *)mlx_get_data_addr(data->mlx_obj, &data->bits, &data->bits, &data->endi);
    data->map_width = 1920;
    data->map_height = 1080;
    player_location(data);
    ft_cam(data);
    mlx_loop_hook(data->mlx_in, &ft_draw, data);
}

int main(int ac, char **av)
{
   (void)ac;
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    fill_map(data, av[1]);

    ft_start(data);

  


}