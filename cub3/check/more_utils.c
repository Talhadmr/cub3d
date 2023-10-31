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
	map->ea = malloc(sizeof(char));
	map->we = malloc(sizeof(char));
	map->so = malloc(sizeof(char));
	map->no = malloc(sizeof(char));
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
	if (map->line)
		free(map->line);
	exit(0);
}

void	set_map_size(char *s, t_map *map)
{
	int		i;
	int		j;
	char	*size;

	i = -1;
	j = -1;
	size = malloc(sizeof(char) * ft_strlen(s));
	while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
		size[++j] = s[i];
	size[++j] = 0;
	map->width = ft_atoi(size);
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	free(size);
	size = malloc(sizeof(char) * ft_strlen(s));
	j = -1;
	i--;
	while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
		size[++j] = s[i];
	size[++j] = 0;
	map->height = ft_atoi(size);
	free(size);
}

void	ft_check_map(t_map *map)
{
	check_up_wall(map);
	check_down_wall(map);
	check_left_wall(map);
	check_right_wall(map);
	check_char(map);
}
