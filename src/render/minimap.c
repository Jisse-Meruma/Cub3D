#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

void	draw_minimap_player(t_cubed *cub)
{
	t_vec	p1;
	t_vec	p2;
	t_vec	p3;

	p1 = vec_rotate(cub->player.dir, 90);
	p3 = vec_rotate(cub->player.dir, -90);
	p1.x = (cub->player.pos.x + p1.x) * cub->mini_ratio;
	p1.y = (cub->player.pos.y + p1.y) * cub->mini_ratio;
	p3.x = (cub->player.pos.x + p3.x) * cub->mini_ratio;
	p3.y = (cub->player.pos.y + p3.y) * cub->mini_ratio;
	p2.x = (cub->player.pos.x + cub->player.dir.x) * cub->mini_ratio;
	p2.y = (cub->player.pos.y + cub->player.dir.y) * cub->mini_ratio;
	draw_line(cub->minimap_view, p1, p2, 0xFFFFFFFF);
	draw_line(cub->minimap_view, p3, p2, 0xFFFFFFFF);
}

void	set_hitpos(t_raycast *r, t_cubed *cub)
{
	if (r->perpwalldist < cub->render_distance)
	{
		r->hit_pos.x = (cub->player.pos.x
				+ r->perpwalldist * r->raydirx) * cub->mini_ratio;
		r->hit_pos.y = (cub->player.pos.y
				+ r->perpwalldist * r->raydiry) * cub->mini_ratio;
	}
	else
	{
		r->hit_pos.x = (cub->player.pos.x
				+ cub->render_distance * r->raydirx) * cub->mini_ratio;
		r->hit_pos.y = (cub->player.pos.y
				+ cub->render_distance * r->raydiry) * cub->mini_ratio;
	}
}

void	draw_minimap(t_raycast r, t_cubed *cub)
{
	t_vec	p1;

	p1.x = cub->player.pos.x * cub->mini_ratio;
	p1.y = cub->player.pos.y * cub->mini_ratio;
	set_hitpos(&r, cub);
	draw_line(cub->minimap, p1, r.hit_pos, 0x999999EE);
	if (r.perpwalldist < cub->render_distance)
	{
		mlx_put_pixel(cub->minimap_view, (int)(r.hit_pos.x),
			(int)(r.hit_pos.y), 0xDDDDDDFF);
		mlx_put_pixel(cub->minimap_explored, (int)(r.hit_pos.x),
			(int)(r.hit_pos.y), 0xAAAAAAFF);
	}
	else
	{
		mlx_put_pixel(cub->minimap_view, (int)(r.hit_pos.x),
			(int)(r.hit_pos.y), 0xDDDDDDFF);
	}
}
