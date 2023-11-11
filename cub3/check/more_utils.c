/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:46:19 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 15:46:21 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_texture(t_map *map)
{
	map->ceiling_color = -1;
	map->floor_color = -1;
	map->width = 1920;
	map->height = 1080;
	map->ea = ft_calloc(1, sizeof(char));
	map->we = ft_calloc(1, sizeof(char));
	map->so = ft_calloc(1, sizeof(char));
	map->no = ft_calloc(1, sizeof(char));
	map->player = 0;
}

void	clear_map(t_map *map, char *error)
{
	int	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	clear_textures(map, error);
}

void	clear_textures(t_map *map, char *error)
{
	if (error)
		printf("%s", error);
	if (map->ea)
		free(map->ea);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->no)
		free(map->no);
	if (map->line && map->line[0])
		free(map->line);
	exit(0);
}

void	ft_check_map(t_map *map)
{
	check_up_wall(map);
	check_down_wall(map);
	check_left_wall(map);
	check_right_wall(map);
	check_char(map);
	if (map->player != 1)
		clear_map(map, "Wrong number of players\n");
}
