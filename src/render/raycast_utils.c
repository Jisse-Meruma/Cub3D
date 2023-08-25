#include <cub3d.h>

void	set_distance(t_raycast *r)
{
	if (r->side == 0)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	else
		r->perpwalldist = (r->sidedisty - r->deltadisty);
}

void	set_hit_position(t_raycast *r, t_vec pos, t_vec raydir)
{
	r->hit_pos.y = pos.y + r->perpwalldist * raydir.y;
	r->hit_pos.x = pos.x + r->perpwalldist * raydir.x;
}
