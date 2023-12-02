/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:14:46 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 16:14:48 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_up_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[0][i] && map->map[0][i] != '\n')
	{
		if (map->map[0][i] == '1')
			i++;
		else if (map->map[0][i] == ' ')
		{
			j = 0;
			while (j < map->map_len)
			{
				if (map->map[j][i] == '1')
				{
					i++;
					break ;
				}
				else
					j += wall_check(map, map->map[j][i]);
			}
		}
		else
			clear_map(map, "Map is not surrounded by walls\n");
	}
}

void	check_down_wall(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[map->map_len - 1][i] && map->map[map->map_len
		- 1][i] != '\n' && map->map[map->map_len - 1][i] != 0)
	{
		if (map->map[map->map_len - 1][i] == '1')
			i++;
		else if (map->map[map->map_len - 1][i] == ' ')
			i = down_wall(map, i);
		else
			clear_map(map, "Map is not surrounded by walls\n");
	}
}

int	down_wall(t_map *map, int i)
{
	int	j;

	j = map->map_len - 1;
	while (map->map[j][i])
	{
		if (map->map[j][i] == '1')
		{
			i++;
			break ;
		}
		else
			j -= wall_check(map, map->map[j][i]);
	}
	return (i);
}

int	wall_check(t_map *map, char c)
{
	if (c == ' ')
		return (1);
	else
		clear_map(map, "Map is not surrounded by walls\n");
	return (0);
}

void	check_ends(t_map *map, int i, int j)
{
	if (i == 0)
		map->up = -1;
	if (i == map->map_len - 1)
		map->down = -1;
	if (j == 0)
		map->left = -1;
	if ((i < map->map_len - 1 && j == ft_strlen(map->c_map[i]) - 2)
		|| (i == map->map_len - 1 && j == ft_strlen(map->c_map[i]) - 1))
		map->right = -1;
}
