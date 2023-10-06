#include <stdio.h>
#include <math.h>

#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define FOV 60
#define PLAYER_SPEED 0.1
#define RAD(x) ((x) * M_PI / 180)

// Harita verisi (1: Duvar, 0: Boş alan)
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

// Oyuncu pozisyon ve görüş açısı
double playerX = 4.5;
double playerY = 4.5;
double playerDirX = 1;
double playerDirY = 0;
double planeX = 0;
double planeY = 0.66;

void castRays()
{
    for (int x = 0; x < 80; x++)
    {
        // Ray'ın yönü ve konumu hesaplanıyor
        double cameraX = 2 * x / (double)80 - 1;
        double rayDirX = playerDirX + planeX * cameraX;
        double rayDirY = playerDirY + planeY * cameraX;

        // Harita üzerindeki hücre
        int mapX = (int)playerX;
        int mapY = (int)playerY;

        // Delta distance (başlangıçta bir hücre içinde gidiş)
        double sideDistX;
        double sideDistY;

        // Delta distance hesaplamaları
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        // Step direction (hücre sınırlarında nasıl adım atılacağı)
        int stepX;
        int stepY;

        // Side and distance calculation
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (playerX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (playerY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
        }

        // DDA (Digital Differential Analyzer) algorithm
        int hit = 0;
        int side;

        while (hit == 0)
        {
            // X veya Y tarafından daha yakın olan hücreye ilerleme
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Harita sınırları kontrolü
            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
                break;

            // Duvar kontrolü
            if (worldMap[mapX][mapY] == 1)
                hit = 1;
        }

        // Perpendicular distance to the wall
        double perpWallDist;
        if (side == 0)
            perpWallDist = (mapX - playerX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - playerY + (1 - stepY) / 2) / rayDirY;

        // Line height
        int lineHeight = (int)(80 / perpWallDist);

        // Draw the wall stripe
        for (int y = -lineHeight / 2 + 40; y < lineHeight / 2 + 40; y++)
        {
            putchar(worldMap[mapX][mapY] == 1 ? '#' : ' ');
        }
    }
}

int main()
{
    while (1)
    {
        // Raycasting fonksiyonunu çağırma
        castRays();

        // Oyuncu kontrolleri buraya eklenebilir

        // Ekran temizleme
        printf("\033[2J");

        // Oyuncu pozisyonunu ekrana basma
        putchar('P');

        // Bekleme süresi
        for (int i = 0; i < 10000000; i++)
            ;
    }

    return 0;
}
