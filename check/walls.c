/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:57:54 by ykissiko          #+#    #+#             */
/*   Updated: 2023/12/05 20:48:49 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_left_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i][0] && i < map->map_len - 1)
	{
		if (map->map[i][0] == '1')
			i++;
		else if (map->map[i][0] == ' ')
		{
			j = 0;
			while (map->map[i][j])
			{
				if (map->map[i][j] == '1')
				{
					i++;
					break ;
				}
				else
					j += wall_check(map, map->map[i][j]);
			}
		}
		else
			clear_map(map, "Map is not surrounded by walls\n");
	}
}

void	check_right_wall(t_map *map)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	y = ft_strlen(map->map[0]) - 2;
	while (i < map->map_len && map->map[i])
	{
		j = ft_strlen(map->map[i]) - 1;
		if (map->map[i][j] == '\n')
			j--;
		while (map->map[i][j] && map->map[i][j] == ' ')
			j--;
		y = right_wall(map, i, y);
		while (y < j)
		{
			if (map->map[i][y] && map->map[i][y] != '1')
				clear_map(map, "Map is not surrounded by walls\n");
			y++;
		}
		if (map->map[i][j] && map->map[i][j] != '1')
			clear_map(map, "Map is not surrounded by walls\n");
		i++;
	}
}

int	right_wall(t_map *map, int i, int y)
{
	if (i - 1 >= 0 && ft_strlen(map->map[i]) > ft_strlen(map->map[i - 1]))
		y = ft_strlen(map->map[i - 1]) - 1;
	if (i + 1 < map->map_len - 1 && i - 1 >= 0
		&& ft_strlen(map->map[i]) > ft_strlen(map->map[i + 1])
		&& ft_strlen(map->map[i + 1]) < ft_strlen(map->map[i - 1]))
		y = ft_strlen(map->map[i + 1]) - 1;
	if (i + 1 == map->map_len - 1
		&& ft_strlen(map->map[i]) > ft_strlen(map->map[i + 1])
		&& ft_strlen(map->map[i + 1]) < ft_strlen(map->map[i - 1]))
		y = ft_strlen(map->map[i + 1]);
	return (y);
}
