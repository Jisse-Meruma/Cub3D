#include <cub3d.h>

void	set_distance(t_raycast *r)
{
	if (r->side == 0 && r->hit == 1)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	else if (r->hit == 1)
		r->perpwalldist = (r->sidedisty - r->deltadisty);
	else
		r->perpwalldist = 0;
}

void	set_hit_position(t_raycast *r, t_vec pos, t_vec raydir)
{
	if (r->hit == 0)
	{
		r->hit_pos = pos;
		r->hit_pos = pos;
	}
	else
	{
		r->hit_pos.y = pos.y + r->perpwalldist * raydir.y;
		r->hit_pos.x = pos.x + r->perpwalldist * raydir.x;
	}
}
