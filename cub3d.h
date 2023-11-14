/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdemir <tdemir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 07:13:42 by tdemir            #+#    #+#             */
/*   Updated: 2023/10/14 07:18:27 by tdemir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RED "\x1b[31m"

typedef struct s_mlx
{
	void		*mlx_init;
	void		*mlx_window;
	void		*mlx_object;
	int			*mlx_object_data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*mlx_img;
}				t_mlx;

typedef struct s_map
{
	char		*ea;
	char		*so;
	char		*we;
	char		*no;
	char		**map;
	long		floor_color;
	long		ceiling_color;
	int			width;
	int			height;
	char		user_type;

	int			map_len;
	char		*line;
	int			player;

}				t_map;

typedef struct s_assets
{
	int			size;
	void		*no;
	int			*no_data;
	int			no_bpp;
	int			no_size_line;
	int			no_endian;

	int			*so_data;
	int			so_bpp;
	int			so_size_line;
	int			so_endian;

	int			*we_data;
	int			we_bpp;
	int			we_size_line;
	int			we_endian;

	int			*ea_data;
	int			ea_bpp;
	int			ea_size_line;
	int			ea_endian;

	void		*so;
	void		*we;
	void		*ea;
}				t_assets;

typedef struct s_rc
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			key_w;
	int			key_s;
	int			key_left;
	int			key_right;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	double		sidedistx;
	double		sidedisty;
	int			wall;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			tex_x;
	int			texnum;
	double		texstep;
	double		texpos;
	int			key_a;
	int			key_d;
}				t_rc;

typedef struct s_cub3d
{
	t_map		map;
	t_mlx		mlx;
	t_assets	assets;
	t_rc		rc;
}				t_cub3d;

void			game(t_cub3d *cub3d);
void			img(t_cub3d *cub3d);
void			user_location(t_cub3d *cub3d);
void			camera(t_cub3d *cub3d);
int				draw(t_cub3d *cub3d);
void			set_variables(t_cub3d *cub3d);
void			ray_casting(t_cub3d *cub3d);
void			ray_casting_send(t_cub3d *cub3d, int x);
void			texture(t_cub3d *cub3d, int x);
int				close_window(int key, void *cub3d);
int				press(int key, void *cub3dd);
int				release(int key, t_cub3d *cub3d);
void			move(t_cub3d *cub3d);
int				is_character(char c);
void			key_d1(t_cub3d *cub3d);
void			key_a1(t_cub3d *cub3d);
void			key_left(t_cub3d *cub3d);
void			key_right(t_cub3d *cub3d);

//CHECK
//check input
int				ft_check_input(int argc, char **argv);
int				ft_check_ext(char *file, int len, char *ext);
void			set_floor_ceiling(char *s, t_map *map, char c);
int				set_color(int i, char *s, short *c, t_map *map);

//check map
int				ft_fill_map(t_map *map, char *argv);

void			set_map_val(char *str, t_map *map);
void			set_map_val2(char *str, char *s, t_map *map);
int				map_start(char *line);
int				check_walls(t_map *map);

//utils
int				ft_atoi(const char *str);
int				str_cmp(char *s1, char *s2);
char			*ft_strdup(char *s1);
int				the_sign(char c);

//walls
void			check_left_wall(t_map *map);
void			check_right_wall(t_map *map);
void			check_char(t_map *map);
int				right_wall(t_map *map, int i, int len);
void			check_spaces(t_map *map);

//wall.c
int				wall_check(t_map *map, char c);
int				down_wall(t_map *map, int i);
void			check_down_wall(t_map *map);
void			check_up_wall(t_map *map);

//map.c
void			ft_set_map(t_map *map, int fd);
void			check_texture(t_map *map);
void			ft_set_textures(t_map *map, int fd);
void			check_after_map(t_map *map, int fd);
char			*str_subjoin(char *s, char c);

//more_utils.c
void			ft_init_texture(t_map *map);
void			clear_textures(t_map *map, char *error);
void			clear_map(t_map *map, char *error);
void			ft_check_map(t_map *map);

//libft_utils
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				empty_line(t_map *map);

#endif