#include "wolf3d.h"



void render(t_wolf3d *w)
{
  register double posX = w->posx, posY = w->posy;  //x and y start position
  register double dirX = w->xdir, dirY = w->ydir; //initial direction vector
  register double planeX = w->xplane, planeY = w->yplane; //the 2d raycaster version of camera plane

    for(int x = 0; x < WIN_W; x++)
    {
      //calculate ray position and direction
      register double cameraX = 2*x/ (double)WIN_W-1; //x-coordinate in camera space
      register double rayDirX = dirX + planeX*cameraX;
      register double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      register double sideDistX;
      register double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      register double deltaDistX = fabs(1 / rayDirX);§
      register double deltaDistY = fabs(1 / rayDirY);
      register double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
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
        //Check if ray has hit a wall
        if (w->map->board[mapX][mapY] > 0) hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(WIN_H / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WIN_H / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + WIN_H / 2;
      if(drawEnd >= WIN_H) drawEnd = WIN_H - 1;

	  int i = -1;
	  while (++i < drawEnd)
	  {
		  put_pixel_img(w, x, i, 0x0000FF);
	  }
      for(int y = drawStart; y < drawEnd; y++)
      {
        put_pixel_img(w, x, y, 0xFF0000);
      }
	  i = drawEnd;
	  while (++i < WIN_H)
	  {
		  put_pixel_img(w, x, i, 0x00FF00);
	  }
    }
}
