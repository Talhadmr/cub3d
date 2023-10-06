#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40
#define FOV M_PI / 3.0
#define PLAYER_SPEED 0.1

typedef struct
{
    double x;
    double y;
    double angle;
} Player;

typedef struct
{
    double x;
    double y;
} Ray;

char worldMap[11][11] = {
    "##########",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "##########"};

void drawMap(Player *player)
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (i == (int)player->y && j == (int)player->x)
                putchar('P'); // Player
            else
                putchar(worldMap[i][j]);
        }
        putchar('\n');
    }
}

void castRays(Player *player)
{
    for (int rayIndex = 0; rayIndex < SCREEN_WIDTH; rayIndex++)
    {
        double rayAngle = player->angle - (FOV / 2) + (rayIndex * FOV / SCREEN_WIDTH);
        double distanceToWall = 0;
        int hitWall = 0;

        double rayX = cos(rayAngle);
        double rayY = sin(rayAngle);

        while (!hitWall && distanceToWall < 16)
        {
            int testX = (int)(player->x + rayX * distanceToWall);
            int testY = (int)(player->y + rayY * distanceToWall);

            if (testX < 0 || testX >= 11 || testY < 0 || testY >= 11 || worldMap[testY][testX] == '#')
            {
                hitWall = 1;
            }
            else
            {
                distanceToWall += 0.1;
            }
        }

        // Calculate the height of the wall based on distance
        int wallHeight = (int)(SCREEN_HEIGHT / distanceToWall);

        // Draw the column for this ray
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            if (y >= (SCREEN_HEIGHT - wallHeight) / 2 && y < (SCREEN_HEIGHT + wallHeight) / 2)
                putchar('#');
            else
                putchar(' ');
        }
    }
}

int main()
{
    Player player = {1.5, 1.5, M_PI / 4}; // Starting position and angle

    while (1)
    {
        // Process input or game logic here

        // Draw the map
        drawMap(&player);

        // Cast rays and draw the 3D view
        castRays(&player);

        // Clear the screen
        system("clear");

        // Update player position or other game state
        player.x += PLAYER_SPEED * cos(player.angle);
        player.y += PLAYER_SPEED * sin(player.angle);

        // Delay to control frame rate
        for (int i = 0; i < 1000000; i++)
            ;
    }

    return 0;
}
