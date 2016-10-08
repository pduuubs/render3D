#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
//bibliothequje graph permettant de faire du pixel a pixel en gros

#define mapWidth 24	//taille de **map
#define mapHeight 24
#define WIDTH 800
#define HEIGHT 600
//une map random trouvée sur internet, elle collera pour le moteur
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

int main(int argc, char const *argv[]) {
	double posX = 22, posY = 11; //coord du joueur
	double dirX = -1, dirY = 0;  //vecteurs cam et direction
	double planeX = 0, planeY = 0.66; //fov

	double time = 0;
	double oldTime = 0;

	screen(WIDTH, HEIGHT, 0, "render3D - pdubs");

	while (!done()) { //boucle de QuickCG, cool et usefull
		for(int x = 0; x < w; x++){
			double cameraX = 2 * x / double(w) - 1;
			double rayPosX = posX;
			double rayPosY = posY;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			int mapX = int(rayPosX);
			int mapY = int(rayPosY);

			double sideDistX, sideDistY;

			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)); //calcul de la distance que le ray a fait d'un x à un autre y
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY)); //mm pour y à y
			double perpWallDist;

			int stepX, stepY;

			int hit = 0; //hit ou non
			int side; //wall type

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

			while (hit == 0){
        if (sideDistX < sideDistY){
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (map[mapX][mapY] > 0) hit = 1;

				if (side == 0){
					perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
				} else {
					perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
				}


				int lineHeight = (int)(h / perpWallDist); //calcul hauteur ligne ecran

				//calculer les bornes de ou on draw les pixels
				int drawStart = -lineHeight / 2 + h / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + h / 2;
				if(drawEnd >= h)drawEnd = h - 1;

					//choose wall color
	      ColorRGB color;
	      switch(map[mapX][mapY]){
	        case 1:  color = RGB_Red;  break; //red
	        case 2:  color = RGB_Green;  break; //green
	        case 3:  color = RGB_Blue;   break; //blue
	        case 4:  color = RGB_White;  break; //white
	        default: color = RGB_Yellow; break; //yellow
	      }

	      if (side == 1) {
					color = color / 2;
				}

				verLine(x, drawStart, drawEnd, color);
			} //fin du DDA

			oldTime = time;
			time = getTicks();
			double frameTime = (time - oldTime) / 1000.0; //temps que la frame a mis pour faire le rendu
			print(1.0 / frameTime); //afficher
			printString("pdubs", WIDTH - 5 * 8, HEIGHT - 8 * 2 - 4, RGB_White);
			printString("alpha 0.0.2 - buggy", WIDTH - 19 * 8, HEIGHT - 8, RGB_White);
			redraw();
			cls();

			//speed modifiers
			double moveSpeed = frameTime * 5.0;
			double rotSpeed = frameTime * 3.0;

			readKeys();
			//move forward if no wall in front of you
			if (keyDown(SDLK_z)){
				if(map[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
				if(map[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
			}
			//move backwards if no wall behind you
			if (keyDown(SDLK_s)){
				if(map[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
				if(map[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
			}
			//rotate to the right
			if (keyDown(SDLK_RIGHT)){
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
				dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
				planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
			}
			//rotate to the left
			if (keyDown(SDLK_LEFT)){
				//both camera direction and camera plane must be rotated
				double oldDirX = dirX;
				dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
				dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
				double oldPlaneX = planeX;
				planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
				planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
			}

			if(keyDown(SDLK_ESCAPE)){
				return 0;
			}
		}
	}
}
