/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:32 by tdemir            #+#    #+#             */
/*   Updated: 2023/12/05 21:09:30 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int key, void *cub3d)
{
	(void)key;
	(void)cub3d;
	exit(0);
}

int	press(int k, void *cub3dd)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3dd;
	if (k == 13)
		cub3d->rc.key_w = 1;
	if (k == 1)
		cub3d->rc.key_s = 1;
	if (k == 123)
		cub3d->rc.key_left = 1;
	if (k == 124)
		cub3d->rc.key_right = 1;
	if (k == 0)
		cub3d->rc.key_a = 1;
	if (k == 2)
		cub3d->rc.key_d = 1;
	else if (k == 53)
	{
		exit(0);
	}
	return (0);
}

int	rele(int k, t_cub3d *cub3d)
{
	if (k == 13)
		cub3d->rc.key_w = 0;
	if (k == 1)
		cub3d->rc.key_s = 0;
	if (k == 123)
		cub3d->rc.key_left = 0;
	if (k == 124)
		cub3d->rc.key_right = 0;
	if (k == 0)
		cub3d->rc.key_a = 0;
	if (k == 2)
		cub3d->rc.key_d = 0;
	return (0);
}
