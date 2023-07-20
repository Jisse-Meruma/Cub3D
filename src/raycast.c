#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>
#include <math.h>
#include <stdint.h>

// Get the relative position on the wall where the ray hit.
float	get_wall_x(t_cubed *cub, t_raycast r, int side)
{
	float	wall_x;


	if (side == 0)
		wall_x = cub->player.pos.y + r.perpWallDist * r.raydirY;
	else
		wall_x = cub->player.pos.x + r.perpWallDist * r.raydirX;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_y(int picture_height, int lineheight, int counter)
{
	float 	step_size;
	float	step_size_picture;
	float	height;

	step_size = (1.0 / (float)lineheight);
	height = ((float)counter * step_size);
	return ((float)picture_height * height);
}


// function to draw a line of the wall.
void	draw_wall_segment(uint32_t x, t_raycast r, t_cubed *cub, int side)
{
	int	lineHeight;
	t_texture *textures;
	int test;
	int	drawstart;
	int	drawend;
	int counter;
	unsigned int	color;
	float			color_falloff;

	counter = 0;
	textures = &cub->map.elements.texture;
	lineHeight = (cub->img->width / r.perpWallDist) / cub->fov;
	drawstart = (-lineHeight / 2) + ((cub->img->height) / 2 + (int)cub->player.head_pitch);
	drawend = (lineHeight / 2) + ((cub->img->height) / 2) + (int)cub->player.head_pitch;
	if (r.perpWallDist / cub->render_distance < 1.0)
		color_falloff = 1 / cos((r.perpWallDist / cub->render_distance) * (M_PI / 2));
	else
	 	color_falloff = 1 / cos(M_PI / 2);
	r.wallX = get_wall_x(cub, r, side);
	r.texX = (double)(textures->north_wall->width * r.wallX); // Replace 255 with the width of the texture.

	int y;
	color = 0xFFFFFFFF;
	y = drawstart;
	test = drawstart;
	
	while (y < drawend)
	{
		if (y >= (int)cub->img->height)
			break ;	
		if (y >= 0)
		{
			// printf("[%d]-%d-\n", get_texture_y(textures->north_wall->height, lineHeight, counter), counter);
			mlx_put_pixel(cub->img, x, y, ((uint32_t *)textures->north_wall->pixels)[(get_texture_y(textures->north_wall->height, lineHeight, counter)) * textures->north_wall->width + r.texX]);
		}
		counter++;
		y++;
	}
}

void	draw_line(t_cubed *cub, t_vec p1, t_vec p2)
{
	int	dx;
	int	dy;
	int	p;
	int	x;
	int	y;

	dx = (int)(p2.x * cub->mini_ratio) - (int)(p1.x * cub->mini_ratio);
	dy = (int)(p2.y * cub->mini_ratio) - (int)(p1.y * cub->mini_ratio);
	x = (int)(p1.x * cub->mini_ratio);
	y = (int)(p1.y * cub->mini_ratio);
	p = (2 * dy) - dx;

	while (x < p2.x * cub->mini_ratio)
	{
		mlx_put_pixel(cub->minimap, x, y, 0xEEEEEEFF);
		if (p >= 0)
		{
			y++;
			p += (2 * dy) - (2 * dx);
		}
		else 
		{
			p += (2 * dy);
		}
		x++;
	}
}

void	draw_minimap(t_raycast r, t_cubed *cub)
{
	if (r.perpWallDist < cub->render_distance)
	{
		r.hit_pos.x = cub->player.pos.x + r.perpWallDist * r.raydirX;
		r.hit_pos.y = cub->player.pos.y + r.perpWallDist * r.raydirY;
		mlx_put_pixel(cub->minimap, (int)(r.hit_pos.x * cub->mini_ratio), (int)(r.hit_pos.y * cub->mini_ratio), 0xFFFFFFFF);
		mlx_put_pixel(cub->minimap_explored, (int)(r.hit_pos.x * cub->mini_ratio), (int)(r.hit_pos.y * cub->mini_ratio), 0xAAAAAAFF);
		draw_line(cub, cub->player.pos, r.hit_pos);
	}
}

// float	get_real_dist(t_cubed *cub, t_raycast r)
// {
// 	float	realDist;
// 	float	Xcomponent;
// 	float	Ycomponent;
//
// 	if (r.side == 1)
// 	{
// 		Xcomponent = cub->player.pos.x + r.mapX;
// 		Ycomponent =  cub->player.pos.y + r.mapY;
// 	}
// 	else
// 	{
// 		Ycomponent = (r.sideDistY - r.deltaDistY) * cub->player.dir.y;
// 		Xcomponent = r.sideDistX * cub->player.dir.x;
//
// 	}
// 	realDist = sqrt((Xcomponent * Xcomponent) + (Ycomponent * Ycomponent));
// 	return (realDist);
// }


/* determine the distance to the first x and first y side
   */
void	init_step_and_side_dist(t_raycast *r, t_cubed *cub)
{
		if (r->raydirX < 0)
		{
			r->stepX = -1;
			r->sideDistX = (cub->player.pos.x - r->mapX) * r->deltaDistX;
		}
		else
		{
			r->stepX = 1;
			r->sideDistX = (r->mapX + 1.0 - cub->player.pos.x) * r->deltaDistX;
		}
		if (r->raydirY < 0)
		{
			r->stepY = -1;
			r->sideDistY = (cub->player.pos.y - r->mapY) * r->deltaDistY;
		}
		else
		{
			r->stepY = 1;
			r->sideDistY = (r->mapY + 1.0 - cub->player.pos.y) * r->deltaDistY;
		}
}



/*
	initialize values needed for the current ray being cast.
	Setting/resetting the current map coordinates.
	Determining the relative x on the "camera plane" position. A value between -1 and 1 with 0 being the middle of the screen and "camera plane".
	Then setting the ray direction. Based on the "camera plane", player direction and camx vectors.
	Then determine the ratio of the ray direction, needed to travel from one side of a square, to the other side of the same square.
	This is not the actual distance but a vector that has the correct ratio.
	This distance is stored as deltaDistX and deltaDistY.
	The square is 1 by 1. So there is an easy way to compute this. If you divide 1 by the x or y component of a vector you get the relative size of each component on its own.
*/
void	init_ray(uint32_t x, t_raycast *r, t_cubed *cub)
{
		r->mapX = (int)cub->player.pos.x;
		r->mapY = (int)cub->player.pos.y;
		r->camx = cub->fov * ((float)x / cub->img->width) - (cub->fov / 2);
		r->raydirX = cub->player.dir.x + (cub->player.c_plane.x) * r->camx;
		r->raydirY = cub->player.dir.y + (cub->player.c_plane.y) * r->camx;
		if (r->raydirX == 0)
			r->deltaDistX = 1e30;
		else
			r->deltaDistX = fabs(1 / r->raydirX);
		if (r->raydirY == 0)
			r->deltaDistY = 1e30;
		else
			r->deltaDistY = fabs(1 / r->raydirY);
		init_step_and_side_dist(r, cub);
		r->hit = 0;
}
/* DDA loop
   here the actual steps are taken to see when a wall is hit.
*/
void	ray_loop(t_raycast *r, t_cubed *cub)
{
		while (r->hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction.
			if (r->sideDistX < r->sideDistY)
			{
				r->sideDistX += r->deltaDistX;
				r->mapX += r->stepX;
				r->side = 0;
			}
			else
			{
				r->sideDistY += r->deltaDistY;
				r->mapY += r->stepY;
				r->side = 1;
			}
			if (r->mapX < cub->map.width && r->mapY < cub->map.height
					&& r->mapX >= 0 && r->mapY >= 0 
					&& cub->map.map[r->mapY][r->mapX] > FLOOR)
				r->hit = 1;
		}
}

/*
	r.mapX and r.mapY represent the current square of the map the ray is in.
	stepX and r.stepY are either -1 or +1 and determine in which direction a step needs to be taken.
	sideDistX and sideDistY are initially the distance the ray has to travel from its start position to the first x side and the first y side.
	Then gets updated to the next x or y side, based on the actual step being taken.
	side determines if the side hit was North South or East West. (NS/Yaxis EW/Xaxis)

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
	uint32_t	x;
	t_raycast	r;

	x = 0;
	ft_bzero(cub->minimap->pixels, sizeof(uint32_t) * cub->minimap->width * cub->minimap->height);
	mlx_put_pixel(cub->minimap, (int)(cub->player.pos.x * cub->mini_ratio), (int)(cub->player.pos.y * cub->mini_ratio), 0xFF0000FF);
	while (x < cub->img->width)
	{
		init_ray(x, &r, cub);
		// perform DDA
		ray_loop(&r, cub);
		// Remove delta distance to get to the side of the 'square' that is next to the wall
		if (r.side == 0)
		{
			r.perpWallDist = (r.sideDistX - r.deltaDistX);
			// r.realWallDist = get_real_dist(cub, r);
		}
		else
		{
			r.perpWallDist = (r.sideDistY - r.deltaDistY);
			// r.realWallDist = get_real_dist(cub, r);
		}
		draw_wall_segment(x, r, cub, r.side);
		draw_minimap(r, cub);
		x++;
	}
}
