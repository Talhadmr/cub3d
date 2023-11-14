/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:52 by tdemir            #+#    #+#             */
/*   Updated: 2023/10/14 07:16:58 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_and_ceiling(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = -1;
	while (++x < cub3d->map.width)
	{
		y = -1;
		while (++y < cub3d->map.height)
		{
			if (y < cub3d->map.height / 2)
				cub3d->mlx.mlx_object_data[y * cub3d->map.width
					+ x] = cub3d->map.ceiling_color;
			else
				cub3d->mlx.mlx_object_data[y * cub3d->map.width
					+ x] = cub3d->map.floor_color;
		}
	}
}

void	clear_img(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx.mlx_init, cub3d->mlx.mlx_object);
	cub3d->mlx.mlx_object = mlx_new_image(cub3d->mlx.mlx_init,
			cub3d->map.width, cub3d->map.height);
	cub3d->mlx.mlx_object_data = (int *)mlx_get_data_addr(cub3d->mlx.mlx_object,
			&cub3d->mlx.bits_per_pixel,
			&cub3d->mlx.size_line,
			&cub3d->mlx.endian);
}

int	draw(t_cub3d *cub3d)
{
	clear_img(cub3d);
	floor_and_ceiling(cub3d);
	ray_casting(cub3d);
	move(cub3d);
	return (0);
}
