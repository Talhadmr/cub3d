#include "../cub3d.h"

int ft_fill_map(t_map *map, char *argv)
{
    int fd;

    fd = open(argv, O_RDONLY);
    ft_set_map(map, fd);
    return (0);
}

void ft_set_map(t_map *map, int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
        check_texture(line, map);
        line = get_next_line(fd);
    }
}

void check_texture(char *line, t_map *map)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        set_map_val("NO", line, map);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        set_map_val("SO", line, map);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        set_map_val("WE", line, map);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        set_map_val("EA", line, map);
    else if (line[0] == 'R' && line[1] == ' ')
        set_map_val("R", line, map);
    else if (line[0] == 'F' && line[1] == ' ')
        set_map_val("F", line, map);
    else if (line[0] == 'C' && line[1] == ' ')
        set_map_val("C", line, map);
}

void set_map_val(char *str, char *line, t_map *map)
{
    int i;
    int j;
    int size;
    char *s;

    i = 0;
    while (str[i] == line[i])
        i++;
    while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
        i++;
    size = ft_strlen(line) - i + 1;
    s = malloc(sizeof(char) * size);
    if (!s)
        return ;
    j = 0;
    while(line[i])
    {
        s[j] = line[i];
        j++;
        i++;
    }
    s[j] = 0;
    free(line);
    set_map_val2(str, s, map);
}

void set_map_val2(char *str, char *s, t_map *map)
{
    if (str_cmp(str, "NO"))
        map->no = ft_strdup(s);
    else if (str_cmp(str, "SO"))
        map->so = ft_strdup(s);
    else if (str_cmp(str, "WE"))
        map->we = ft_strdup(s);
    else if (str_cmp(str, "EA"))
        map->ea = ft_strdup(s);
    else if (str_cmp(str, "R"))
        set_map_size(s, map);
    else if (str_cmp(str, "F"))
        set_floor_color(s, map);
    else if (str_cmp(str, "C"))
        set_ceiling_color(s, map);
    free(s);
}

void set_ceiling_color(char *s, t_map *map)
{
    int i;
    int j;
    char *color;

    i = -1;
    color = malloc(sizeof(char) * ft_strlen(s));
    j = -1;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->c_red = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    j = -1;
    i--;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->c_green = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    j = -1;
    i--;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->c_blue = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    if (!(map->c_red >= 0 && map->c_red <= 255) || !(map->c_blue >= 0 && map->c_blue <= 255) || !(map->c_green >= 0 && map->c_green <= 255))
    {
        printf("Wrong colors\n");
        return ;
    }
    else
        map->ceiling_color = (map->c_red << 16) + (map->c_green << 8) + map->c_blue;
    printf("Ceiling %ld\n", map->ceiling_color);
}

void set_floor_color(char *s, t_map *map)
{
    int i;
    int j;
    char *color;

    i = -1;
    color = malloc(sizeof(char) * ft_strlen(s));
    j = -1;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->f_red = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    j = -1;
    i--;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->f_green = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    j = -1;
    i--;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        color[++j] = s[i];
    color[++j] = 0;
    map->f_blue = ft_atoi(color);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13) || s[i] == ','))
        i++;
    if (!(map->f_red >= 0 && map->f_red <= 255) || !(map->f_blue >= 0 && map->f_blue <= 255) || !(map->f_green >= 0 && map->f_green <= 255))
    {
        printf("Wrong colors\n");
        return ;
    }
    else
        map->floor_color = (map->f_red << 16) + (map->f_green << 8) + map->f_blue;
     printf("Floor %ld\n", map->floor_color);
}

void set_map_size(char *s, t_map *map)
{
    int i;
    int j;
    char *size;

    i = -1;
    j = -1;
    size = malloc(sizeof(char) * ft_strlen(s) + 1);
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        size[++j] = s[i];
    size[++j] = 0;
    map->width = ft_atoi(size);
    while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
        i++;
    //free(size);
    //size = malloc(sizeof(char) * ft_strlen(s) + 1);
    j = -1;
    i--;
    while (s[++i] && (s[i] >= '0' && s[i] <= '9'))
        size[++j] = s[i];
    size[++j] = 0;
    map->height = ft_atoi(size);
    free(size);
}


