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
			map->c_map[i] = ft_strdup(map->line);
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
		if (map_start(map->line) == 1)
		{
			map->map_len = 1;
			break ;
		}
		check_texture(map);
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
	check_after_map(map, fd);
	free(map->line);
}

void	check_after_map(t_map *map, int fd)
{
	while (map->line != NULL && empty_line(map))
	{
		free(map->line);
		map->line = get_next_line(fd);
	}
	if (map->line != NULL && !empty_line(map))
		clear_textures(map, "Nothing should be defined after map\n");
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
	else if (map->line[0] == 'F' && map->line[1] == ' ')
		set_map_val("F", map);
	else if (map->line[0] == 'C' && map->line[1] == ' ')
		set_map_val("C", map);
	else if (!empty_line(map))
		clear_textures(map, "Undefined characters\n");
}

char	*str_subjoin(char *s, char c)
{
	int		len;
	char	*str;
	int		i;

	len = 0;
	if (s)
		len = ft_strlen(s);
	str = malloc(len + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	if (s)
		free(s);
	return (str);
}
