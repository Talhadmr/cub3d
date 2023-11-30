/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:40:59 by ykissiko          #+#    #+#             */
/*   Updated: 2023/11/30 04:59:03 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_setting(t_map *map)
{
	if (map->ceiling_color == -1 || map->floor_color == -1)
		clear_textures(map, "Colors not set\n");
	if (!map->ea[1] || !map->no[1] || !map->so[1] || !map->we[1])
		clear_textures(map, "Side textures are not set\n");
}

int	ft_fill_map(t_map *map, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	ft_init_texture(map);
	ft_set_textures(map, fd);
	close(fd);
	if (map->map_len > 0)
	{
		map->map = malloc(sizeof(char *) * map->map_len + 1);
		if (!map->map)
			return (0);
	}
	else
		clear_textures(map, "No map in the file\n");
	ft_check_setting(map);
	fd = open(argv, O_RDONLY);
	ft_set_map(map, fd);
	close(fd);
	ft_check_map(map);
	return (0);
}

int	map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	else if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W') && (line[i + 1] == '0' || line[i + 1] == '1'))
		return (1);
	return (0);
}

void	set_map_val(char *str, t_map *map)
{
	int		i;
	int		j;
	int		size;
	char	*s;

	i = 0;
	while (str[i] == map->line[i])
		i++;
	while (map->line[i] == ' ' || (map->line[i] >= 9 && map->line[i] <= 13))
		i++;
	size = ft_strlen(map->line) - i + 1;
	s = malloc(sizeof(char) * size);
	if (!s)
		return ;
	j = 0;
	while (map->line[i] && map->line[i] != '\n')
	{
		s[j] = map->line[i];
		j++;
		i++;
	}
	s[j] = 0;
	set_map_val2(str, s, map);
}

void	set_map_val2(char *str, char *s, t_map *map)
{
	int fd;
	
	if (str_cmp(str, "NO"))
	{
		fd = open(s, O_RDONLY);
		
		if (fd == -1)
			clear_textures(map, "NO texture not found\n");
		else if (fd != -1)
		{
			free(map->no);
			map->no = ft_strdup(s);
			close(fd);
		}
	}
	else if (str_cmp(str, "SO"))
	{
		fd = open(s, O_RDONLY);
		
		if (fd == -1)
			clear_textures(map, "SO texture not found\n");
		else if (fd != -1)
		{
			free(map->so);
			map->so = ft_strdup(s);
			close(fd);
		}

	}
	else if (str_cmp(str, "WE"))
	{
		fd = open(s, O_RDONLY);
		if (fd == -1)
			clear_textures(map, "WE texture not found\n");
		else if (fd != -1)
		{
			free(map->we);
			map->we = ft_strdup(s);
			close(fd);
		}
	}
	else if (str_cmp(str, "EA"))
	{

		fd = open(s, O_RDONLY);
		if (fd == -1)
			clear_textures(map, "EA texture not found\n");
		else if (fd != -1)
		{
			free(map->ea);
			map->ea = ft_strdup(s);
			close(fd);
		}
	}
	else if (str_cmp(str, "F"))
		set_floor_ceiling(s, map, 'F');
	else if (str_cmp(str, "C"))
		set_floor_ceiling(s, map, 'C');
	free(s);
}
