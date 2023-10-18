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
void fill_map(t_cub3d	*cub3d, char *str)
{
    int fd;
    fd = open(str, O_RDONLY);
    cub3d->map.map = malloc(sizeof(char *) * 7);
    cub3d->map.map[0] = get_next_line(3);
    cub3d->map.map[1] = get_next_line(3);
    cub3d->map.map[2] = get_next_line(3);
    cub3d->map.map[3] = get_next_line(3);
    cub3d->map.map[4] = get_next_line(3);
    cub3d->map.map[5] = get_next_line(3);
    cub3d->map.map[6] = get_next_line(3);

    cub3d->map.no = strdup("textures/text1.xpm");
    cub3d->map.ea = strdup("textures/text2.xpm");
    cub3d->map.we = strdup("textures/text3.xpm");
    cub3d->map.so= strdup("textures/text4.xpm");
	int f0 = 90;
	int f1 = 0;
	int f2 = 22;

	int c0 = 20;
	int c1 = 105;
	int c2 = 100;

	cub3d->map.floor_color = (f0 << 16) + (f1 << 8) + f2;
	cub3d->map.ceiling_color = (c0 << 16) + (c1 << 8) + c2;
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;
    //t_map map;
	(void)ac;
	cub3d = (t_cub3d *)malloc(sizeof(t_cub3d));

    if (ft_check_input(ac, av) != 1)
        return (0);
    printf("start processing map\n");
    ft_fill_map(&cub3d->map, av[1]);
	//fill_map(cub3d, av[1]);
    printf("in game\n");
    printf("floor %ld, ceiling %ld\nNO %s, EA %s, WE %s, SO %s\n", cub3d->map.floor_color, cub3d->map.ceiling_color, cub3d->map.no, cub3d->map.ea, cub3d->map.we, cub3d->map.so);
    int i = -1;
    while (++i < cub3d->map.map_len)
        printf("%s", cub3d->map.map[i]);
	game(cub3d);
}
