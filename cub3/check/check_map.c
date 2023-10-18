#include "../cub3d.h"

int ft_fill_map(t_map *map, char *argv)
{
    int fd;

    fd = open(argv, O_RDONLY);
    ft_set_textures(map, fd);
    close(fd);
    fd = open(argv, O_RDONLY);
    ft_set_map(map, fd);
    close(fd);
    ft_check_map(map);
    //printf("map is checked\n");
    return (0);
}

void ft_check_map(t_map *map)
{
    if (check_up_wall(map) != 1)
        return ;
    if (check_down_wall(map) != 1)
        return ;
    if (check_left_wall(map) != 1)
        return ;
    if (check_right_wall(map) != 1)
        return ;
    if (check_char(map) != 1)
        return ;
}

void ft_set_map(t_map *map, int fd)
{
    char *line;
    int i;

    line = get_next_line(fd);
    i = 0;
    while (line != NULL)
    {
        if (map_start(line) == 1)
        {
            map->map[i] = ft_strdup(line);
            map->c_map[i] = ft_strdup(line);
            i++;
        }
        line = get_next_line(fd);
    }
    // i = -1;
    // while (map->map[++i])
    //     printf("%s", map->map[i]);
}

void ft_set_textures(t_map *map, int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
        check_texture(line, map);
        if (map_start(line) == 1)
        {
            map->map_len = 1;
            break ;
        }
        line = get_next_line(fd);
    }
    line = get_next_line(fd);
    while (line != NULL && map_start(line) == 1)
    {
        map->map_len++;
        line = get_next_line(fd);
    }
    map->map = malloc(sizeof(char *) * map->map_len + 1);
    map->c_map = malloc(sizeof(char *) * map->map_len + 1);
    if (!map->map || !map->c_map)
        return ;
    // printf("map size %d\n", map->map_len);
    // printf("textures done\n");
}

int map_start(char *line)
{
    int i;

    i = 0;
    while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
        i++;
    //printf("in map start, %d i %c\n", i,  line[i]);
    if (line[i] == '1')
        return (1);
    return(0);
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
    else if (line[0] == 'R' && line[1] == ' ') //OPTIONAL
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
    while(line[i] && line[i] != '\n')
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
    //printf("Ceiling %ld\n", map->ceiling_color);
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
     //printf("Floor %ld\n", map->floor_color);
}

void set_map_size(char *s, t_map *map) //I DONT NEED IT I GUESS
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
    //map->width = ft_atoi(size);
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


