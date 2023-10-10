#include "cub3d.h"
void	set_value(t_cub3d *cub3d)
{
	double	wallx;

	cub3d->rc.texnum = cub3d->map.map[cub3d->rc.mapx][cub3d->rc.mapy] - 1;
	if (cub3d->rc.side == 0)
		wallx = cub3d->rc.posy + cub3d->rc.perpwalldist * cub3d->rc.raydiry;
	else
		wallx = cub3d->rc.posx + cub3d->rc.perpwalldist * cub3d->rc.raydirx;
	wallx -= floor(wallx);
	cub3d->rc.tex_x = (int)(wallx * (double)64);
	if (cub3d->rc.side == 0 && cub3d->rc.raydirx > 0)
		cub3d->rc.tex_x = 64 - cub3d->rc.tex_x - 1;
	if (cub3d->rc.side == 1 && cub3d->rc.raydiry < 0)
		cub3d->rc.tex_x = 64 - cub3d->rc.tex_x - 1;
	cub3d->rc.texstep = 1.0 * 64 / cub3d->rc.lineheight;
	cub3d->rc.texpos = (cub3d->rc.drawstart - 1080 / 2 + cub3d->rc.lineheight
			/ 2) * cub3d->rc.texstep;
}

void	texture(t_cub3d *cub3d, int x)
{
	int	texy;

	set_value(cub3d);
	while (cub3d->rc.drawstart < cub3d->rc.drawend)
	{
		texy = (int)cub3d->rc.texpos & 63;
		cub3d->rc.texpos += cub3d->rc.texstep;
		if (cub3d->rc.side == 0 && cub3d->rc.raydirx > 0)
			cub3d->mlx.mlx_object_data[cub3d->rc.drawstart * 1920
				+ x] = cub3d->assets.so_data[64 * texy + cub3d->rc.tex_x];
		else if (cub3d->rc.side == 0 && cub3d->rc.raydirx < 0)
			cub3d->mlx.mlx_object_data[cub3d->rc.drawstart * 1920
				+ x] = cub3d->assets.no_data[64 * texy + cub3d->rc.tex_x];
		else if (cub3d->rc.side == 1 && cub3d->rc.raydiry > 0)
			cub3d->mlx.mlx_object_data[cub3d->rc.drawstart * 1920
				+ x] = cub3d->assets.ea_data[64 * texy + cub3d->rc.tex_x];
		else
			cub3d->mlx.mlx_object_data[cub3d->rc.drawstart * 1920
				+ x] = cub3d->assets.we_data[64 * texy + cub3d->rc.tex_x];
		cub3d->rc.drawstart++;
	}
}