/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:46:53 by ykissiko          #+#    #+#             */
/*   Updated: 2023/12/05 21:05:04 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	space_sur(t_map *map, int i, int j)
{
	if (j + 1 < ft_strlen(map->map[i]) && (map->map[i][j + 1] == '0'
		|| player(map->map[i][j + 1])))
		clear_map(map, "Spaces in the wrong place\n");
	else if (j > 0 && (map->map[i][j - 1] == '0' || player(map->map[i][j - 1])))
		clear_map(map, "Spaces in the wrong place\n");
	else if (i + 1 < map->map_len && (map->map[i + 1][j] == '0'
		|| player(map->map[i + 1][j])))
		clear_map(map, "Spaces in the wrong place\n");
	else if (i > 0 && (map->map[i - 1][j] == '0' || player(map->map[i - 1][j])))
		clear_map(map, "Spaces in the wrong place\n");
}

void	check_spaces(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->map_len && map->map[i])
	{
		j = 0;
		while (j < ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == ' ')
				space_sur(map, i, j);
			j++;
		}
	}
}

void	path_loop(t_map *map, int i, int j)
{
	if (player(map->c_map[i][j]))
		map->player++;
	map->c_map[i][j] = '.';
	if (i > 0 && (map->c_map[i - 1][j] == '0' || map->c_map[i - 1][j] == '1'
			|| player(map->c_map[i - 1][j])))
		path_loop(map, i - 1, j);
	if (i < map->map_len - 1 && (map->c_map[i + 1][j] == '0' || map->c_map[i
			+ 1][j] == '1' || player(map->c_map[i + 1][j])))
		path_loop(map, i + 1, j);
	if (j > 0 && (map->c_map[i][j - 1] == '0' || map->c_map[i][j - 1] == '1'
			|| player(map->c_map[i][j - 1])))
		path_loop(map, i, j - 1);
	if (j < ft_strlen(map->c_map[i]) - 1 && (map->c_map[i][j + 1] == '0'
		|| map->c_map[i][j + 1] == '1' || player(map->c_map[i][j + 1])))
		path_loop(map, i, j + 1);
}

void	check_path(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < map->map_len && map->c_map[i])
	{
		j = 0;
		len = ft_strlen(map->c_map[i]);
		while (j < len && map->c_map[i][j] == ' ')
			j++;
		if (map->c_map[i][j] == '1' || map->c_map[i][j] == '0'
			|| player(map->c_map[i][j]))
		{
			path_loop(map, i, j);
			break ;
		}
		else if (map->c_map[i][j] != '\n' && map->c_map[i][j] != '\0')
			clear_map(map, "Some undefined characters\n");
	}
	check_path2(map);
}

void	check_path2(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < map->map_len && map->c_map[i])
	{
		j = 0;
		len = ft_strlen(map->c_map[i]);
		while (j < len)
		{
			if (map->c_map[i][j] == '.' || map->c_map[i][j] == ' '
				|| map->c_map[i][j] == '\n' || map->c_map[i][j] == 0)
				j++;
			else if (map->c_map[i][j] == '1' || map->c_map[i][j] == '0'
					|| player(map->c_map[i][j]))
				clear_map(map, "Unconnected maps are not supported\n");
			else
				clear_map(map, "Some undefined characters\n");
		}
	}
}
