/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:57:54 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 15:57:55 by ykissiko         ###   ########.fr       */
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
	int	len;

	i = 0;
	len = ft_strlen(map->map[i]) - 1;
	while (map->map[i][len] && i < map->map_len - 1)
	{
		if (map->map[i][len] == '\n')
			len--;
		if (map->map[i][len] == '1')
			i++;
		else if (map->map[i][len] == ' ')
			right_wall(map, i, len);
		else
			clear_map(map, "Map is not surrounded by walls\n");
		len = ft_strlen(map->map[i]) - 1;
	}
}

int	right_wall(t_map *map, int i, int len)
{
	int	j;

	j = len;
	while (map->map[i][j])
	{
		if (map->map[i][j] == '1')
		{
			i++;
			break ;
		}
		else
			j -= wall_check(map, map->map[i][j]);
	}
	return (i);
}

void	check_char(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i] && i < map->map_len - 1)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1' || map->map[i][j] == '0'
				|| map->map[i][j] == ' ')
				j++;
			else if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player++;
				j++;
			}
			else if (map->map[i][j] == '\n')
				break ;
			else
				clear_map(map, "Map has some undefined chars");
		}
		i++;
	}
}
