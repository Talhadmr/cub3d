/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:40:59 by ykissiko          #+#    #+#             */
/*   Updated: 2023/12/05 19:05:11 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	int	fd;

	if (str_cmp(str, "NO") || str_cmp(str, "SO")
		|| str_cmp(str, "EA") || str_cmp(str, "WE"))
	{
		fd = open(s, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			clear_textures(map, "Cannot open textures file\n");
		}
		close(fd);
	}
	else if (str_cmp(str, "F"))
		set_floor_ceiling(s, map, 'F');
	else if (str_cmp(str, "C"))
		set_floor_ceiling(s, map, 'C');
	if (str_cmp(str, "NO"))
	{
		if (map->no[0])
			clear_textures(map, "Duplicated NO texture\n");
		free(map->no);
		map->no = ft_strdup(s);
	}
	set_map_val3(str, s, map);
}

void	set_map_val3(char *str, char *s, t_map *map)
{
	if (str_cmp(str, "SO"))
	{
		if (map->so[0])
			clear_textures(map, "Duplicated SO texture\n");
		free(map->so);
		map->so = ft_strdup(s);
	}
	else if (str_cmp(str, "WE"))
	{
		if (map->we[0])
			clear_textures(map, "Duplicated WE texture\n");
		free(map->we);
		map->we = ft_strdup(s);
	}
	else if (str_cmp(str, "EA"))
	{
		if (map->ea[0])
			clear_textures(map, "Duplicated EA texture\n");
		free(map->ea);
		map->ea = ft_strdup(s);
	}
	free(s);
}
