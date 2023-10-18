#include "../cub3d.h"

int	check_up_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->c_map[0][i] && map->c_map[0][i] != '\n')
	{
		if (map->c_map[0][i] == '1')
			i++;
		else if (map->c_map[0][i] == ' ')
		{
			j = 0;
			while (map->c_map[j][i])
			{
				if (map->c_map[j][i] == '1')
				{
					i++;
					break ;
				}
				else if (map->c_map[j][i] == ' ')
					j++;
				else
					return (printf("Map is not surrounded by walls\n"));
			}
		}
		else
			return (printf("Map is not surrounded by walls\n"));
	}
	return (1);
}

int	check_down_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->c_map[map->map_len - 1][i] && map->c_map[map->map_len
		- 1][i] != '\n' && map->c_map[map->map_len - 1][i] != 0)
	{
		if (map->c_map[map->map_len - 1][i] == '1')
			i++;
		else if (map->c_map[map->map_len - 1][i] == ' ')
		{
			j = map->map_len - 1;
			while (map->c_map[j][i])
			{
				if (map->c_map[j][i] == '1')
				{
					i++;
					break ;
				}
				else if (map->c_map[j][i] == ' ')
					j--;
				else
					return (printf("Map is not surrounded by walls\n"));
			}
		}
		else
			return (printf("Map is not surrounded by walls\n"));
	}
	return (1);
}

int	check_left_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->c_map[i][0] && i < map->map_len - 1)
	{
		if (map->c_map[i][0] == '1')
			i++;
		else if (map->c_map[i][0] == ' ')
		{
			j = 0;
			while (map->c_map[i][j])
			{
				if (map->c_map[i][j] == '1')
				{
					i++;
					break ;
				}
				else if (map->c_map[i][j] == ' ')
					j++;
				else
					return (printf("Map is not surrounded by walls\n"));
			}
		}
		else
			return (printf("Map is not surrounded by walls\n"));
	}
	return (1);
}
int	check_right_wall(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(map->c_map[i]) - 1;
	while (map->c_map[i][len] && i < map->map_len - 1)
	{
		if (map->c_map[i][len] == '\n')
			len--;
		if (map->c_map[i][len] == '1')
			i++;
		else if (map->c_map[i][len] == ' ')
		{
			j = len;
			while (map->c_map[i][j])
			{
				if (map->c_map[i][j] == '1')
				{
					i++;
					break ;
				}
				else if (map->c_map[i][j] == ' ')
					j--;
				else
					return (printf("Map is not surrounded by walls\n"));
			}
		}
		else
			return (printf("Map is not surrounded by walls\n"));
		len = ft_strlen(map->c_map[i]) - 1;
	}
	return (1);
}

int check_char(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->c_map[i] && i < map->map_len - 1)
    {
        j = 0;
        while (map->c_map[i][j])
        {
            if (map->c_map[i][j] == '1' || map->c_map[i][j] == '0' || map->c_map[i][j] == 'N' || map->c_map[i][j] == 'S' || map->c_map[i][j] == 'E' || map->c_map[i][j] == 'W' || map->c_map[i][j] == ' ')
                j++;
            else if (map->c_map[i][j] == '\n')
                break ;
            else
                return (printf("Map has some undefined chars '%c'\n", map->c_map[i][j]));
        }
        i++;
    }
    return (1);
}