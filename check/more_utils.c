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
	map->ea = ft_calloc(1, sizeof(char));
	map->we = ft_calloc(1, sizeof(char));
	map->so = ft_calloc(1, sizeof(char));
	map->no = ft_calloc(1, sizeof(char));
	map->player = 0;
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
	if (map->line && map->line[0])
		free(map->line);
	exit(0);
}

void	ft_check_map(t_map *map)
{
	// check_up_wall(map);
	// check_down_wall(map);
	// check_left_wall(map);
	// check_right_wall(map);
	check_all_walls(map);
	check_char(map);
	check_spaces(map);
	if (map->player != 1)
		clear_map(map, "Wrong number of players\n");
}

void check_all_walls(t_map *map)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	j = 0;

	printf("start left\n");
	while (map->map[i])
	{
		while (i < map->map_len && map->map[i][j] && map->map[i][j] == '1')
			i++;
		if (i < map->map_len && map->map[i][j] && map->map[i][j] == ' ')
		{
			while (map->map[i][j] && map->map[i][j] == ' ')
				j++;
			if (map->map[i][j] && map->map[i][j] != '1')
				clear_map(map, "left 1 Map is not surrounded by walls\n");
			i++;
			j = 0;
		}
		else if (i < map->map_len && map->map[i][j] && map->map[i][j] != '\n')
			clear_map(map, "left 2 Map is not surrounded by walls\n");
	}
	i = 0;
	j = 0;
	printf("start up\n");
	while (map->map[i] && map->map[i][j])
	{
		while (map->map[i][j] && map->map[i][j] == '1')
			j++;
		if (map->map[i][j] && map->map[i][j] == ' ')
		{
			while (map->map[i][j] && map->map[i][j] == ' ')
				i++;
			if (map->map[i][j] != '1' || i == map->map_len - 1)		//what if the beginning has 'spaces'
				clear_map(map, "up 1 Map is not surrounded by walls\n");
			j++;
			i = 0;
		}
		else if (map->map[i][j] && map->map[i][j] != '\n')
			clear_map(map, "up 2 Map is not surrounded by walls\n");
	}
	
	printf("start right\n");
	y = j;
	while (i < map->map_len && map->map[i])
	{
		j = ft_strlen(map->map[i]) - 1;
		if (map->map[i][j] == '\n')
			j--;
		if (ft_strlen(map->map[i]) > y)
		{
			y -= 2;
			while (y < j)
			{
				if (map->map[i][y] && (map->map[i][y] != '1' || map->map[i][y] != ' '))
					clear_map(map, "right 1Map is not surrounded by walls\n");
				y++;
			}
			y = ft_strlen(map->map[i]);
		}
		if (map->map[i][j] && (map->map[i][y] != '1' || map->map[i][y] != ' '))
			clear_map(map, "right 2Map is not surrounded by walls\n");
		i++;
	}

	i--;
	printf("start down\n");
	x = i;
	while (map->map[i] && map->map[i][j])
	{
		while (j >= 0 && map->map[i][j] == '1')
			j--;
		if (j >= 0 && map->map[i][j] == ' ')
		{
			while (map->map[i][j] && map->map[i][j] == ' ')
				i--;
			if (map->map[i][j] != '1' || i == 0)		//what if the beginning has 'spaces'
				clear_map(map, "down 1 Map is not surrounded by walls\n");
			j--;
			i = map->map_len - 1;
		}
		else
			clear_map(map, "down 2 Map is not surrounded by walls\n");
	}
}