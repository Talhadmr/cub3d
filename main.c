#include "cub3d.h"
fill_map()
void player_location(t_data *data)
{

}
int main()
{
    t_data data;

    data.mlx_in = mlx_init();
    data.mlx_w = mlx_new_window(data.mlx_in, 1920, 1080, "CUB3D");
    data.mlx_obj = mlx_new_image(data.mlx_in, 1920, 1080);
    data.mlx_info = mlx_get_data_addr(data.mlx_obj, data.bits, data.bits, data.endi);

    data.map_width = 1920;
    data.map_height = 1080;
    fill_map(data);
    player_location(data);

}