#include <cub3d.h>
#include <math.h>
#include <stdint.h>

/* determine the distance to the first x and first y side
   */
void	init_step_and_side_dist(t_raycast *r, t_vec pos, t_vec raydir)
{
	if (raydir.x < 0)
	{
		r->stepx = -1;
		r->sidedistx = (pos.x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - pos.x) * r->deltadistx;
	}
	if (raydir.y < 0)
	{
		r->stepy = -1;
		r->sidedisty = (pos.y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - pos.y) * r->deltadisty;
	}
}

/*
	initialize values needed for the current ray being cast.
	Setting/resetting the current map coordinates.
	Determining the relative x on the "camera plane" position.
	A value between -1 and 1 with 0 being
	the middle of the screen and "camera plane".
	Then setting the ray direction. Based on the "camera plane",
	player direction and camx vectors.
	Then determine the ratio of the ray direction,
	needed to travel from one side of a square,
	to the other side of the same square.
	This is not the actual distance but a vector that has the correct ratio.
	This distance is stored as deltadistx and deltadisty.
	The square is 1 by 1. So there is an easy way to compute this.
	If you divide 1 by the x or y component of a
	vector you get the relative size of each component on its own.
*/
void	init_ray(t_raycast *r, t_vec pos, t_vec raydir)
{
	r->mapx = (int)pos.x;
	r->mapy = (int)pos.y;
	if (raydir.x == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / raydir.x);
	if (raydir.y == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / raydir.y);
	init_step_and_side_dist(r, pos, raydir);
	r->hit = 0;
}

/* DDA loop
   here the actual steps are taken to see when a wall is hit.
*/
void	ray_loop(t_raycast *r, t_map map)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (r->mapx < map.width
			&& r->mapy < map.height
			&& r->mapx >= 0 && r->mapy >= 0
			&& map.tiles[r->mapy][r->mapx] > FLOOR)
			r->hit = 1;
	}
}

/*
	r.mapx and r.mapy represent the current square of the map the ray is in.
	stepx and r.stepy are either -1 or +1 and determine in
	which direction a step needs to be taken.
	sidedistx and sidedisty are initially the distance the ray has to travel
	from its start position to the first x side and the first y side.
	Then gets updated to the next x or y side, based on the actual step being taken.
	side determines if the side hit was North South or East West.
	(NS/Yaxis EW/Xaxis)

	Now the actual DDA starts.
	It's a loop that increments the ray with 1 square every time,
	until a wall is hit.
	Each time, either it jumps a square in the x-direction (with stepx) or a square
	in the y-direction (with r.stepy), it always jumps 1 square at once.
	If the ray's direction would be the x-direction,
	the loop will only have to jump
	a square in the x-direction everytime,
	because the ray will never change its y-direction.
	If the ray is a bit sloped to the y-direction,
	then every so many jumps in the x-direction,
	the ray will have to jump one square in the y-direction.
	If the ray is exactly the y-direction,
	it never has to jump in the x-direction, etc...
	sidedistx and sidedisty get incremented with
	deltadistx with every jump in their direction,
	and r.mapx and r.mapy get incremented with stepx and r.stepy respectively.
*/
t_raycast_info	raycast(t_vec pos, t_vec dir, t_map map)
{
	t_raycast		r;
	t_raycast_info	inf;

	init_ray(&r, pos, dir);
	ray_loop(&r, map);
	set_distance(&r);
	set_hit_position(&r, pos, dir);
	r.raydirx = dir.x;
	r.raydiry = dir.y;
	inf.dir = dir;
	inf.start = pos;
	inf.perpwalldist = r.perpwalldist;
	inf.hit_pos = r.hit_pos;
	inf.side = r.side;
	return (inf);
}
