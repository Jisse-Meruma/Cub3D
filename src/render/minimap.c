/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:52 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:22:53 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	mlx_put_pixel(cub->minimap_view,
		(int)(cub->player.pos.x * cub->mini_ratio),
		(int)(cub->player.pos.y * cub->mini_ratio), 0xFFFFFFFF);
}

static void	set_p2(t_raycast_info *r, t_cubed *cub, t_vec *pos)
{
	if (r->perpwalldist < cub->render_distance)
	{
		pos->x = (r->hit_pos.x) * cub->mini_ratio;
		pos->y = (r->hit_pos.y) * cub->mini_ratio;
	}
	else
	{
		pos->x = (int)((cub->player.pos.x
					+ cub->render_distance * r->dir.x) * cub->mini_ratio);
		pos->y = (int)((cub->player.pos.y
					+ cub->render_distance * r->dir.y) * cub->mini_ratio);
	}
}

void	draw_minimap(t_raycast_info r, t_cubed *cub)
{
	t_vec	p1;
	t_vec	p2;

	p1.x = cub->player.pos.x * cub->mini_ratio;
	p1.y = cub->player.pos.y * cub->mini_ratio;
	set_p2(&r, cub, &p2);
	draw_line(cub->minimap, p1, p2, 0x999999EE);
	if (r.perpwalldist < cub->render_distance)
	{
		mlx_put_pixel(cub->minimap_view, p2.x, p2.y, 0xDDDDDDFF);
		mlx_put_pixel(cub->minimap_explored, p2.x, p2.y, 0xAAAAAAFF);
	}
	else
	{
		mlx_put_pixel(cub->minimap_view, p2.x, p2.y, 0xDDDDDDFF);
	}
}
