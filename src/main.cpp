#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <string>

#include "quickcg.h" //biblio graphique

#define mapWidth 24
#define mapHeight 24
#define WIDTH 800
#define HEIGHT 600

int map[mapWidth][mapHeight] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

using namespace QuickCG;
using namespace std;

std::string VERSION ("alpha 0.1.0");
int VERSIONl = 11;
double posX = 22, posY = 11;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;
int running = 1;

void render(double posX, double posY, double dirX, double dirY, double planeX, double planeY);
void tick();

int main(){


	screen(WIDTH, HEIGHT, 0, "render3D - pdubs - " + VERSION);

	while (running) {
			render(posX, posY, dirX, dirY, planeX, planeY);
			tick();
	}
}

void render(double posX, double posY, double dirX, double dirY, double planeX, double planeY){
	for(int x = 0; x < w	; x++){
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

			if (rayDirX < 0){
				stepX = -1;
				sideDistX = (rayPosX - mapX) * deltaDistX;
			} else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
			}
			if (rayDirY < 0){
				stepY = -1;
				sideDistY = (rayPosY - mapY) * deltaDistY;
			} else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
			}
			//DDA
			while (hit == 0)
			{
				if (sideDistX < sideDistY){
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

			if (side == 0){
				perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
			} else {
				perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
			}

			int lineHeight = (int)(h / perpWallDist);

			int drawStart = -lineHeight / 2 + h / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if(drawEnd >= h)drawEnd = h - 1;

			ColorRGB color;
			switch(map[mapX][mapY]){
				case 1:  color = RGB_Red;  break; //red
				case 2:  color = RGB_Green;  break; //green
				case 3:  color = RGB_Blue;   break; //blue
				case 4:  color = RGB_White;  break; //white
				default: color = RGB_Yellow; break; //yellow
			}


			if (side == 1){
				color = color / 2;
			}

			verLine(x, drawStart, drawEnd, color);
	}
//	print(1.0 / frameTime);
	printString("pdubs", WIDTH - 5 * 8 + 1 - 8, HEIGHT - 8 * 2 - 8 + 1, RGB_Black);
	printString(VERSION, WIDTH - VERSIONl * 8 - 8, HEIGHT - 8 + 1  - 4, RGB_Black);
	printString("pdubs", WIDTH - 5 * 8 - 8, HEIGHT - 8 * 2 - 8, RGB_White);
	printString(VERSION, WIDTH - VERSIONl * 8 - 8, HEIGHT - 8  - 4, RGB_White);

	redraw();
	cls();
}

void tick(){
	double time = 0;
	double oldTime = 0;

	oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0;

	double moveSpeed = frameTime * 5.0;
	double rotSpeed = frameTime * 3.0;


	readKeys();

	if (keyDown(SDLK_z) || keyDown(SDLK_UP)){
		if(map[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		if(map[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}

	if (keyDown(SDLK_s) || keyDown(SDLK_DOWN)){
		if(map[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		if(map[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
	}


	if (keyDown(SDLK_RIGHT) || keyDown(SDLK_d)){
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}

	if (keyDown(SDLK_LEFT) || keyDown(SDLK_q)){
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}

	if(keyDown(SDLK_ESCAPE)){
		running = 0;
	}
}
