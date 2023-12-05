/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:13:20 by tdemir            #+#    #+#             */
/*   Updated: 2023/12/05 20:01:22 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_w(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->rc.posx + cub3d->rc.dirx
			* 0.08)][(int)(cub3d->rc.posy)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx + cub3d->rc.dirx
				* 0.08)][(int)(cub3d->rc.posy)]))
		cub3d->rc.posx += cub3d->rc.dirx * 0.08;
	if (cub3d->map.map[(int)cub3d->rc.posx][(int)(cub3d->rc.posy
		+ cub3d->rc.diry * 0.08)] == '0'
		|| is_character(cub3d->map.map[(int)cub3d->rc.posx][(int)(cub3d->rc.posy
				+ cub3d->rc.diry * 0.08)]))
		cub3d->rc.posy += cub3d->rc.diry * 0.08;
}

void	key_s(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->rc.posx - cub3d->rc.dirx
			* 0.08)][(int)(cub3d->rc.posy)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx - cub3d->rc.dirx
				* 0.08)][(int)(cub3d->rc.posy)]))
		cub3d->rc.posx -= cub3d->rc.dirx * 0.08;
	if (cub3d->map.map[(int)(cub3d->rc.posx)][(int)(cub3d->rc.posy
			- cub3d->rc.diry * 0.08)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx)][
			(int)(cub3d->rc.posy - cub3d->rc.diry * 0.08)]))
		cub3d->rc.posy -= cub3d->rc.diry * 0.08;
}

void	key_a(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->rc.posx + cub3d->rc.diry
			* 0.08)][(int)(cub3d->rc.posy)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx + cub3d->rc.diry
				* 0.08)][(int)(cub3d->rc.posy)]))
		cub3d->rc.posx += cub3d->rc.diry * 0.08;
	if (cub3d->map.map[(int)(cub3d->rc.posx)][(int)(cub3d->rc.posy
			- cub3d->rc.dirx * 0.08)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx)]
		[(int)(cub3d->rc.posy - cub3d->rc.dirx * 0.08)]))
		cub3d->rc.posy -= cub3d->rc.dirx * 0.08;
}

void	key_d(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->rc.posx - cub3d->rc.diry
			* 0.08)][(int)(cub3d->rc.posy)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx - cub3d->rc.diry
				* 0.08)][(int)(cub3d->rc.posy)]))
		cub3d->rc.posx -= cub3d->rc.diry * 0.08;
	if (cub3d->map.map[(int)(cub3d->rc.posx)][(int)(cub3d->rc.posy
			+ cub3d->rc.dirx * 0.08)] == '0'
		|| is_character(cub3d->map.map[(int)(cub3d->rc.posx)]
		[(int)(cub3d->rc.posy + cub3d->rc.dirx * 0.08)]))
		cub3d->rc.posy += cub3d->rc.dirx * 0.08;
}

void	movement(t_cub3d *cub3d)
{
	if (cub3d->rc.key_w)
		key_w(cub3d);
	if (cub3d->rc.key_s)
		key_s(cub3d);
	if (cub3d->rc.key_left)
		key_left(cub3d);
	if (cub3d->rc.key_right)
		key_right(cub3d);
	if (cub3d->rc.key_a)
		key_a(cub3d);
	if (cub3d->rc.key_d)
		key_d(cub3d);
}
