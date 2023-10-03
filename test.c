#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include "mlx/mlx.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60
#define PLAYER_SPEED 5

typedef struct
{
    double x;
    double y;
    double angle;
} Player;

void draw_line(int x1, int y1, int x2, int y2, int color, void *mlx_ptr, void *win_ptr)
{
    // MinilibX ile çizgi çizme fonksiyonu
    // Bu fonksiyonu daha geniş bir grafik işleme kütüphanesi ile değiştirebilirsiniz

    mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
}

void cast_rays(Player *player, void *mlx_ptr, void *win_ptr)
{
    int num_rays = SCREEN_WIDTH;

    for (int ray = 0; ray < num_rays; ray++)
    {
        double angle = player->angle - (FOV / 2) + (ray * FOV / SCREEN_WIDTH);
        double x_step = cos(angle);
        double y_step = sin(angle);

        double x = player->x;
        double y = player->y;

        while (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        {
            // Ekrana çizgi çizme fonksiyonu
            draw_line(player->x, player->y, x, y, 0xFBFFFF, mlx_ptr, win_ptr);

            x += x_step;
            y += y_step;
        }
    }
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    Player player;

    // MinilibX penceresi oluşturma
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting Example");

    // Oyuncu başlangıç pozisyonu
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.angle = 0;

    // Ana oyun döngüsü
    while (1)
    {
        // Oyuncu kontrolleri burada eklenebilir

        // Raycasting fonksiyonunu çağırma
        cast_rays(&player, mlx_ptr, win_ptr);

        // MinilibX ile pencereyi güncelleme
        mlx_loop(mlx_ptr);
    }

    return 0;
}
