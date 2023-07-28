#include "MLX42.h"
#include "struct.h"
# include <cub3d.h>
# include <math.h>
#include <stdbool.h>
#include <stdint.h>

void	draw_minimap_player(t_cubed *cub)
{
	t_vec	p1;
	t_vec	p2;
	t_vec	p3;
	// t_vec	p4;

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

bool	in_image(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x > 0 && x < img->width && y > 0 && y < img->height);
}

void	draw_line(mlx_image_t *img, t_vec p1, t_vec p2, unsigned int color)
{
	int	dx;
	int	dy;
	float	x;
	float	y;

	dx = (int)(p2.x) - (int)(p1.x);
	dy = (int)(p2.y) - (int)(p1.y);
	x = p1.x;
	y = p1.y;
	if (abs(dx) > abs(dy))
	{
		while ((int)x != (int)(p2.x) && in_image(img, x, y))
		{
			mlx_put_pixel(img, round(x), round(y), color);
			y += (float)dy / abs(dx);
			x += (float)dx / abs(dx);
		}
	}
	else
	{
		while ((int)y != (int)(p2.y) && in_image(img, x, y))
		{
			mlx_put_pixel(img, round(x), round(y), color);
			x += (float)dx / abs(dy);
			y += (float)dy / abs(dy);
		}
	}
}

void	draw_minimap(t_raycast r, t_cubed *cub)
{
	t_vec	p1;

	p1.x = cub->player.pos.x * cub->mini_ratio;
	p1.y = cub->player.pos.y * cub->mini_ratio;
	if (r.perpWallDist < cub->render_distance)
	{
		r.hit_pos.x = (cub->player.pos.x + r.perpWallDist * r.raydirX) * cub->mini_ratio;
		r.hit_pos.y = (cub->player.pos.y + r.perpWallDist * r.raydirY) * cub->mini_ratio;
		draw_line(cub->minimap, p1, r.hit_pos, 0x999999EE);
		mlx_put_pixel(cub->minimap_view, (int)(r.hit_pos.x), (int)(r.hit_pos.y), 0xDDDDDDFF);
		mlx_put_pixel(cub->minimap_explored, (int)(r.hit_pos.x), (int)(r.hit_pos.y), 0xAAAAAAFF);
	}
	else 
	{	
		r.hit_pos.x = (cub->player.pos.x + cub->render_distance * r.raydirX) * cub->mini_ratio;
		r.hit_pos.y = (cub->player.pos.y + cub->render_distance * r.raydirY) * cub->mini_ratio;
		draw_line(cub->minimap, p1, r.hit_pos, 0x999999EE);
		mlx_put_pixel(cub->minimap_view, (int)(r.hit_pos.x), (int)(r.hit_pos.y), 0xDDDDDDFF);
	}
}



