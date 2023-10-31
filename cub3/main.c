/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:49 by tdemir            #+#    #+#             */
/*   Updated: 2023/10/14 07:18:08 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	(void)ac;
	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (ft_check_input(ac, av) != 1)
		return (0);
	ft_fill_map(&cub3d->map, av[1]);
	game(cub3d);
}
