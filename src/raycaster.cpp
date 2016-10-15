#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graphics/pdubscg_all.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define WIDTH 800
#define HEIGHT 600

int map[mapWidth][mapHeight] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

using namespace std;

std::string VERSION ("alpha 0.2.0");
int VERSIONl = 11;
double posX = 22, posY = 11;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;
int running = 1;

Uint32 buffer[HEIGHT][WIDTH];
std::vector<int> texture[8];

void render(double posX, double posY, double dirX, double dirY, double planeX, double planeY);

int main(int argc, char **argv){

        bool fullscreen = 0;
        bool debug = 0;
        int c;

        while ((c = getopt (argc, argv, "fd")) != -1)
        {
                switch (c)
                {
                case 'f':
                        fullscreen = 1;
                        break;
                case 'd':
                        debug = 1;
                        break;
                }
        }

        double time = 0;         //time of current frame
        double oldTime = 0;         //time of previous frame

        for(int i = 0; i < 8; i++) texture[i].resize(texWidth * texHeight);

        initScreen(WIDTH, HEIGHT, fullscreen, "render3D - pdubs - " + VERSION);

        for(int x = 0; x < texWidth; x++)
                for(int y = 0; y < texHeight; y++)
                {
                        int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
                        int ycolor = y * 256 / texHeight;
                        int xycolor = y * 128 / texHeight + x * 128 / texWidth;
                        texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
                        texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
                        texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
                        texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
                        texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
                        texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
                        texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
                        texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
                }

        //a remplacer par une methode plus précise comme un tick sur l'horloge microseconde
        while(running)
        {
                render(posX, posY, dirX, dirY, planeX, planeY);
                oldTime = time;
                time = getTicks();
                double frameTime = (time - oldTime) / 1000.0;
                double moveSpeed = frameTime * 5.0;                 //csnt squares/second
                double rotSpeed = frameTime * 3.0;                 //csnt radians/second

                readKeys();
                if (keyDown(SDLK_UP))
                {
                        if(map[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
                        if(map[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
                }
                if (keyDown(SDLK_DOWN))
                {
                        if(map[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
                        if(map[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
                }
                //right
                if (keyDown(SDLK_RIGHT))
                {
                        //matrice de rotation
                        double oldDirX = dirX;
                        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                }
                //left
                if (keyDown(SDLK_LEFT))
                {
                        //matrice de rotation
                        double oldDirX = dirX;
                        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                }

                if(keyDown(SDLK_ESCAPE)) {
                        running = 0;
                }
        }
}

void render(double posX, double posY, double dirX, double dirY, double planeX, double planeY){
        for(int x = 0; x < WIDTH; x++) {
                double cameraX = 2 * x / double(w) - 1;
                double rayPosX = posX;
                double rayPosY = posY;
                double rayDirX = dirX + planeX * cameraX;
                double rayDirY = dirY + planeY * cameraX;
                int mapX = int(rayPosX);
                int mapY = int(rayPosY);
                double sideDistX;
                double sideDistY;
                double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
                double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
                double perpWallDist;
                int stepX;
                int stepY;
                int hit = 0;
                int side;

                if (rayDirX < 0) {
                        stepX = -1;
                        sideDistX = (rayPosX - mapX) * deltaDistX;
                } else {
                        stepX = 1;
                        sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
                }
                if (rayDirY < 0) {
                        stepY = -1;
                        sideDistY = (rayPosY - mapY) * deltaDistY;
                } else {
                        stepY = 1;
                        sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
                }
                //DDA
                while (hit == 0)
                {
                        if (sideDistX < sideDistY) {
                                sideDistX += deltaDistX;
                                mapX += stepX;
                                side = 0;
                        } else {
                                sideDistY += deltaDistY;
                                mapY += stepY;
                                side = 1;
                        }
                        if (map[mapX][mapY] > 0) hit = 1;
                }

                if (side == 0) {
                        perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
                } else {
                        perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
                }

                int lineHeight = (int)(h / perpWallDist);

                int drawStart = -lineHeight / 2 + h / 2;
                if(drawStart < 0) drawStart = 0;
                int drawEnd = lineHeight / 2 + h / 2;
                if(drawEnd >= h) drawEnd = h - 1;


                //texturing calculations
                int texNum = map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

                //calculate value of wallX
                double wallX; //where exactly the wall was hit
                if (side == 0) wallX = rayPosY + perpWallDist * rayDirY;
                else wallX = rayPosX + perpWallDist * rayDirX;
                wallX -= floor((wallX));

                //x coordinate on the texture
                int texX = int(wallX * double(texWidth));
                if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
                if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

                for(int y = drawStart; y<drawEnd; y++)
                {
                        int d = y * 256 - h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
                        int texY = ((d * texHeight) / lineHeight) / 256;
                        Uint32 color = texture[texNum][texHeight * texY + texX];
                        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
                        if(side == 1) color = (color >> 1) & 8355711;
                        buffer[y][x] = color;
                }

                drawBuffer(buffer[0]);
                for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) buffer[y][x] = 0;

        }
}
