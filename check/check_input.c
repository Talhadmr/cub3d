/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:40:21 by ykissiko          #+#    #+#             */
/*   Updated: 2023/10/31 15:40:23 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_input(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Wrong number of arguments\n"));
	if (ft_check_ext(argv[1], 4, ".cub") != 1)
		return (printf("Map have to be in .cub file format\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("Map doesn't exist\n"));
	close(fd);
	return (1);
}

int	ft_check_ext(char *file, int len, char *ext)
{
	int	flen;
	int	i;

	flen = ft_strlen(file);
	i = 0;
	while (i < len)
	{
		if (file[flen - len + i] != ext[i])
			return (0);
		i++;
	}
	return (1);
}

void	set_floor_ceiling(char *s, t_map *map, char c)
{
	int		i;
	short	red;
	short	green;
	short	blue;

	if (c == 'F' && map->floor_color != -1)
		clear_textures(map, "Duplicated floor colors\n");
	else if (c == 'C' && map->ceiling_color != -1)
		clear_textures(map, "Duplicated ceiling colors\n");
	i = 0;
	i = set_color(i, s, &red, map);
	if (s[i] != ',')
		clear_textures(map, "Wrong format for colors, add only 1 comma\n");
	i++;
	i = set_color(i, s, &green, map);
	if (s[i] != ',')
		clear_textures(map, "Wrong format for colors, add only 1 comma\n");
	i++;
	i = set_color(i, s, &blue, map);
	if (i < ft_strlen(s))
		clear_textures(map, "Wrong format for colors\n");
	if (c == 'F')
		map->floor_color = (red << 16) + (green << 8) + blue;
	else if (c == 'C')
		map->ceiling_color = (red << 16) + (green << 8) + blue;
}

int	set_color(int i, char *s, short *c, t_map *map)
{
	char	*color;

	color = ft_calloc(1, sizeof(char));
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			color = str_subjoin(color, s[i]);
		else if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ',')
			break ;
		else
		{
			free(color);
			clear_textures(map, "Wrong colors\n");
		}
		i++;
	}
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	*c = ft_atoi(color);
	free(color);
	if (!(*c >= 0 && *c <= 255))
		clear_textures(map, "Wrong colors\n");
	return (i);
}

void	ft_check_setting(t_map *map)
{
	if (map->ceiling_color == -1 || map->floor_color == -1)
		clear_textures(map, "Colors not set\n");
	if (!map->ea[0] || !map->no[0] || !map->so[0] || !map->we[0])
		clear_textures(map, "Side textures are not set\n");
}
