/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:45 by tdemir            #+#    #+#             */
/*   Updated: 2023/12/05 20:04:18 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	imgs(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 64;
	y = 64;
	cub3d->assets.no = mlx_xpm_file_to_image(cub3d->mlx.mlx_init, cub3d->map.no,
			&x, &y);
	cub3d->assets.no_data = (int *)mlx_get_data_addr(cub3d->assets.no,
			&cub3d->assets.no_bpp, &cub3d->assets.no_size_line,
			&cub3d->assets.no_endian);
	cub3d->assets.we = mlx_xpm_file_to_image(cub3d->mlx.mlx_init, cub3d->map.we,
			&x, &y);
	cub3d->assets.we_data = (int *)mlx_get_data_addr(cub3d->assets.we,
			&cub3d->assets.we_bpp, &cub3d->assets.we_size_line,
			&cub3d->assets.we_endian);
	cub3d->assets.so = mlx_xpm_file_to_image(cub3d->mlx.mlx_init, cub3d->map.so,
			&x, &y);
	cub3d->assets.so_data = (int *)mlx_get_data_addr(cub3d->assets.so,
			&cub3d->assets.so_bpp, &cub3d->assets.so_size_line,
			&cub3d->assets.so_endian);
	cub3d->assets.ea = mlx_xpm_file_to_image(cub3d->mlx.mlx_init, cub3d->map.ea,
			&x, &y);
	cub3d->assets.ea_data = (int *)mlx_get_data_addr(cub3d->assets.ea,
			&cub3d->assets.ea_bpp, &cub3d->assets.ea_size_line,
			&cub3d->assets.ea_endian);
}

void	user_location(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (cub3d->map.map[x])
	{
		y = 0;
		while (cub3d->map.map[x][y])
		{
			if (cub3d->map.map[x][y] == 'N' || cub3d->map.map[x][y] == 'S'
				|| cub3d->map.map[x][y] == 'W' || cub3d->map.map[x][y] == 'E')
			{
				cub3d->rc.posx = x + 0.5;
				cub3d->rc.posy = y + 0.5;
				cub3d->map.user_type = cub3d->map.map[x][y];
				return ;
			}
			y++;
		}
		x++;
	}
}

void	render(t_cub3d *cub3d)
{
	cub3d->mlx.mlx_init = mlx_init();
	cub3d->mlx.mlx_window = mlx_new_window(cub3d->mlx.mlx_init,
			cub3d->map.width, cub3d->map.height, "CUB3D");
	cub3d->mlx.mlx_object = mlx_new_image(cub3d->mlx.mlx_init, cub3d->map.width,
			cub3d->map.height);
	cub3d->mlx.mlx_object_data = (int *)mlx_get_data_addr(cub3d->mlx.mlx_object,
			&cub3d->mlx.bits_per_pixel, &cub3d->mlx.size_line,
			&cub3d->mlx.endian);
	set_variables(cub3d);
	mlx_loop_hook(cub3d->mlx.mlx_init, &rend, cub3d);
	mlx_hook(cub3d->mlx.mlx_window, 2, 0, &press, cub3d);
	mlx_hook(cub3d->mlx.mlx_window, 3, 0, &rele, cub3d);
	mlx_hook(cub3d->mlx.mlx_window, 17, 1L << 17, &close_window, cub3d);
	mlx_loop(cub3d->mlx.mlx_init);
}
