/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:55 by tdemir            #+#    #+#             */
/*   Updated: 2023/10/14 07:16:51 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	direction(t_cub3d *cub3d)
{
	if (cub3d->rc.raydirx < 0)
	{
		cub3d->rc.stepx = -1;
		cub3d->rc.sidedistx = (cub3d->rc.posx - cub3d->rc.mapx)
			* cub3d->rc.deltadistx;
	}
	else
	{
		cub3d->rc.stepx = 1;
		cub3d->rc.sidedistx = (cub3d->rc.mapx + 1.0 - cub3d->rc.posx)
			* cub3d->rc.deltadistx;
	}
	if (cub3d->rc.raydiry < 0)
	{
		cub3d->rc.stepy = -1;
		cub3d->rc.sidedisty = (cub3d->rc.posy - cub3d->rc.mapy)
			* cub3d->rc.deltadisty;
	}
	else
	{
		cub3d->rc.stepy = 1;
		cub3d->rc.sidedisty = (cub3d->rc.mapy + 1.0 - cub3d->rc.posy)
			* cub3d->rc.deltadisty;
	}
}

void	wallhit(t_cub3d *cub3d)
{
	cub3d->rc.wall = 0;
	while (!cub3d->rc.wall)
	{
		if (cub3d->rc.sidedistx < cub3d->rc.sidedisty)
		{
			cub3d->rc.sidedistx += cub3d->rc.deltadistx;
			cub3d->rc.mapx += cub3d->rc.stepx;
			cub3d->rc.side = 0;
		}
		else
		{
			cub3d->rc.sidedisty += cub3d->rc.deltadisty;
			cub3d->rc.mapy += cub3d->rc.stepy;
			cub3d->rc.side = 1;
		}
		if (cub3d->map.map[cub3d->rc.mapx][cub3d->rc.mapy] == '1')
			cub3d->rc.wall = 1;
	}
}

void	raydist(t_cub3d *cub3d)
{
	if (cub3d->rc.side == 0)
		cub3d->rc.perpwalldist = cub3d->rc.sidedistx - cub3d->rc.deltadistx;
	else
		cub3d->rc.perpwalldist = cub3d->rc.sidedisty - cub3d->rc.deltadisty;
	cub3d->rc.lineheight = (int)(1080 / cub3d->rc.perpwalldist);
	cub3d->rc.drawstart = -cub3d->rc.lineheight / 2 + 1080 / 2;
	if (cub3d->rc.drawstart < 0)
		cub3d->rc.drawstart = 0;
	cub3d->rc.drawend = cub3d->rc.lineheight / 2 + 1080 / 2;
	if (cub3d->rc.drawend >= 1080)
		cub3d->rc.drawend = 1080 - 1;
}

void	ray_casting(t_cub3d *cub3d)
{
	int	x;

	x = 0;
	while (x < 1920)
	{
		cub3d->rc.camerax = 2 * x / (double)1920 - 1;
		cub3d->rc.raydirx = cub3d->rc.dirx + cub3d->rc.planex
			* cub3d->rc.camerax;
		cub3d->rc.raydiry = cub3d->rc.diry + cub3d->rc.planey
			* cub3d->rc.camerax;
		cub3d->rc.mapx = (int)cub3d->rc.posx;
		cub3d->rc.mapy = (int)cub3d->rc.posy;
		cub3d->rc.deltadistx = fabs(1 / cub3d->rc.raydirx);
		cub3d->rc.deltadisty = fabs(1 / cub3d->rc.raydiry);
		direction(cub3d);
		wallhit(cub3d);
		raydist(cub3d);
		texture(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx.mlx_init, cub3d->mlx.mlx_window,
		cub3d->mlx.mlx_object, 0, 0);
}
