#include "MLX42.h"
#include <cub3d.h>
#include <math.h>


// function to draw a line of the wall.
void	draw_wall_segment(int x, float perpWallDist, int scale, t_cubed *cub, int side)
{
	int	lineHeight;
	int	drawstart;
	int	drawend;
	unsigned int	color;

	printf("perpWallDist: %f\n", perpWallDist);
	lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
	drawstart = (-lineHeight / 2) + ((WINDOW_HEIGHT) / 2);
	if (drawstart < 0)
		drawstart = 0;
	drawend = (lineHeight / 2) + ((WINDOW_HEIGHT) / 2);
	if (drawend >= WINDOW_HEIGHT * scale)
		drawend = (WINDOW_HEIGHT * scale) - 1;
	color = 0xFF00FFFF;
	if (side == 1)
		color = color / 2;
	int y;
	y = drawstart;
	//printf("drawstart: %i, drawend: %i\n", drawstart, drawend);
	while (y <= drawend)
	{
		mlx_put_pixel(cub->img, x, y, color);
		y++;
	}
}

/*
	r.mapX and r.mapY represent the current square of the map the ray is in.
	stepX and r.stepY are either -1 or +1 and determine in which direction a step needs to be taken.
	sideDistX and sideDistY are initially the distance the ray has to travel from its start position to the first x side and the first y side.

	side determines if the side hit was NS or EW

	Now the actual DDA starts.
	It's a loop that increments the ray with 1 square every time, until a wall is hit.
	Each time, either it jumps a square in the x-direction (with stepX) or a square in the y-direction (with r.stepY), it always jumps 1 square at once.
	If the ray's direction would be the x-direction, the loop will only have to jump a square in the x-direction everytime, because the ray will never change its y-direction.
	If the ray is a bit sloped to the y-direction, then every so many jumps in the x-direction, the ray will have to jump one square in the y-direction.
	If the ray is exactly the y-direction, it never has to jump in the x-direction, etc...
	sideDistX and sideDistY get incremented with deltaDistX with every jump in their direction, and r.mapX and r.mapY get incremented with stepX and r.stepY respectively.
*/
void	raycast(t_cubed *cub)
{
	int	x;
	t_raycast	r;

	x = 0;
	printf("playerXY: %f,%f\n", cub->player.pos.x, cub->player.pos.y);
	while (x < WINDOW_WIDTH)
	{
		r.mapX = (int)cub->player.pos.x;
		r.mapY = (int)cub->player.pos.y;
		mlx_put_pixel(cub->img, x, WINDOW_HEIGHT / 2, 0xFF00FFFF);
		r.camx = (float)((2 * x) / (float)WINDOW_WIDTH) - 1.0;
		r.raydirX = cub->player.dir.x + cub->player.c_plane.x * r.camx;
		r.raydirY = cub->player.dir.y + cub->player.c_plane.y * r.camx;
		printf("playerdirXY: %f, %f\ncplaneXY:%f, %f\n",cub->player.dir.x, cub->player.dir.y, cub->player.c_plane.x, cub->player.c_plane.y);
		if (r.raydirX == 0)
			r.deltaDistX = 1e30;
		else
			r.deltaDistX = fabs(1 / r.raydirX);
		if (r.raydirY == 0)
			r.deltaDistY = 1e30;
		else
			r.deltaDistY = fabs(1 / r.raydirY);
		// calculate step and initial sideDist 
		if (r.raydirX < 0)
		{
			r.stepX = -1;
			r.sideDistX = (cub->player.pos.x - r.mapX) * r.deltaDistX;
		}
		else
		{
			r.stepX = 1;
			r.sideDistX = (r.mapX + 1.0 - cub->player.pos.x) * r.deltaDistX;
		}
		if (r.raydirY < 0)
		{
			r.stepY = -1;
			r.sideDistY = (cub->player.pos.y - r.mapY) * r.deltaDistY;
		}
		else
		{
			r.stepY = 1;
			r.sideDistY = (r.mapY + 1.0 - cub->player.pos.y) * r.deltaDistY;
		}
		r.hit = 0;
		// perform DDA
		while (r.hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction.
			if (r.sideDistX < r.sideDistY)
			{
				r.sideDistX += r.deltaDistX;
				r.mapX += r.stepX;
				r.side = 0;
			}
			else
			{
				r.sideDistY += r.deltaDistY;
				r.mapY += r.stepY;
				r.side = 1;
			}
			if (r.mapX < cub->map.width && r.mapY < cub->map.height
					&& r.mapX >= 0 && r.mapY >= 0 
					&& cub->map.map[r.mapY][r.mapX] > (t_tile)1)
				r.hit = 1;
			mlx_put_pixel(cub->img, r.mapX, r.mapY, 0xFF0000FF);
			printf("mapX: %i, mapY: %i\n", r.mapX, r.mapY);
			// r.hit = 1;
		}
		printf("sideDistX: %f, sideDistY: %f\n", r.sideDistX, r.sideDistY);
		if (r.side == 0)
			r.perpWallDist = (r.sideDistX - r.deltaDistX);
		else
			r.perpWallDist = (r.sideDistY - r.deltaDistY);
		draw_wall_segment(x, r.perpWallDist, 1, cub, r.side);
		x++;
	}
}
