/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:55:08 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 15:55:09 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_map(t_map *map, int fd)
{
	int	i;

	map->line = get_next_line(fd);
	i = 0;
	while (map->line != NULL)
	{
		if (map_start(map->line) == 1)
		{
			map->map[i] = ft_strdup(map->line);
			i++;
		}
		free(map->line);
		map->line = get_next_line(fd);
	}
	free(map->line);
}

void	ft_set_textures(t_map *map, int fd)
{
	map->line = get_next_line(fd);
	while (map->line != NULL)
	{
		check_texture(map);
		if (map_start(map->line) == 1)
		{
			map->map_len = 1;
			break ;
		}
		free(map->line);
		map->line = get_next_line(fd);
	}
	free(map->line);
	map->line = get_next_line(fd);
	while (map->line != NULL && map_start(map->line) == 1)
	{
		map->map_len++;
		free(map->line);
		map->line = get_next_line(fd);
	}
	map->map = malloc(sizeof(char *) * map->map_len + 1);
	if (!map->map)
		return ;
	free(map->line);
}

void	check_texture(t_map *map)
{
	if (map->line[0] == 'N' && map->line[1] == 'O' && map->line[2] == ' ')
		set_map_val("NO", map);
	else if (map->line[0] == 'S' && map->line[1] == 'O' && map->line[2] == ' ')
		set_map_val("SO", map);
	else if (map->line[0] == 'W' && map->line[1] == 'E' && map->line[2] == ' ')
		set_map_val("WE", map);
	else if (map->line[0] == 'E' && map->line[1] == 'A' && map->line[2] == ' ')
		set_map_val("EA", map);
	else if (map->line[0] == 'R' && map->line[1] == ' ')
		set_map_val("R", map);
	else if (map->line[0] == 'F' && map->line[1] == ' ')
		set_map_val("F", map);
	else if (map->line[0] == 'C' && map->line[1] == ' ')
		set_map_val("C", map);
}

int	set_color(int i, char *s, short *c, t_map *map)
{
	int		j;
	char	*color;

	color = malloc(sizeof(char) * 4);
	if (!color)
		return (-1);
	j = -1;
	while (s[++i] && (s[i] >= '0' && s[i] <= '9') && j < 3)
		color[++j] = s[i];
	if (j == 3)
	{
		free(color);
		clear_textures(map, "Wrong colors\n");
	}
	color[++j] = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
		i++;
	*c = ft_atoi(color);
	if (!(*c >= 0 && *c <= 255))
	{
		free(color);
		clear_textures(map, "Wrong colors\n");
	}
	free(color);
	return (i);
}

void	set_floor_ceiling(char *s, t_map *map, char c)
{
	int		i;
	short	red;
	short	green;
	short	blue;

	i = -1;
	i = set_color(i, s, &red, map) - 1;
	i = set_color(i, s, &green, map) - 1;
	i = set_color(i, s, &blue, map) - 1;
	if (c == 'F')
		map->floor_color = (red << 16) + (green << 8) + blue;
	else if (c == 'C')
		map->ceiling_color = (red << 16) + (green << 8) + blue;
}
