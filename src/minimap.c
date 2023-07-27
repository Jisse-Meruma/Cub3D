# include <cub3d.h>
# include <math.h>

void	draw_line(t_cubed *cub, t_vec p1, t_vec p2)
{
	int	dx;
	int	dy;
	// int	p;
	float	x;
	float	y;

	dx = (int)(p2.x * cub->mini_ratio) - (int)(p1.x * cub->mini_ratio);
	dy = (int)(p2.y * cub->mini_ratio) - (int)(p1.y * cub->mini_ratio);
	x = (int)(p1.x * cub->mini_ratio);
	y = (int)(p1.y * cub->mini_ratio);
	// p = (2 * dy) - dx;

	// while ((int)x != (int)(p2.x * cub->mini_ratio) && (int)y != (int)(p2.y * cub->mini_ratio))
	// {
		// mlx_put_pixel(cub->minimap, (int)x, (int)y, 0xEEEEEEFF);
		// if (p >= 0)
		// {
		// 	y++;
		// 	p += (2 * dy) - (2 * dx);
		// }
		// else 
		// {
		// 	p += (2 * dy);
		if (abs(dx) > abs(dy))
		{
			while ((int)x != (int)(p2.x * cub->mini_ratio))
			{
				mlx_put_pixel(cub->minimap, round(x), round(y), 0x999999EE);
				y += (float)dy / abs(dx);
				x += (float)dx / abs(dx);
			}
		}
		else
		{
			while ((int)y != (int)(p2.y * cub->mini_ratio))
			{
				mlx_put_pixel(cub->minimap, round(x), round(y), 0x999999EE);
				x += (float)dx / abs(dy);
				y += (float)dy / abs(dy);
			}
		}
	// }
}

void	draw_minimap(t_raycast r, t_cubed *cub)
{
	if (r.perpWallDist < cub->render_distance)
	{
		r.hit_pos.x = cub->player.pos.x + r.perpWallDist * r.raydirX;
		r.hit_pos.y = cub->player.pos.y + r.perpWallDist * r.raydirY;
		draw_line(cub, cub->player.pos, r.hit_pos);
		mlx_put_pixel(cub->minimap, (int)(r.hit_pos.x * cub->mini_ratio), (int)(r.hit_pos.y * cub->mini_ratio), 0xFFFFFFFF);
		mlx_put_pixel(cub->minimap_explored, (int)(r.hit_pos.x * cub->mini_ratio), (int)(r.hit_pos.y * cub->mini_ratio), 0xAAAAAAFF);
	}
	else 
	{	
		r.hit_pos.x = cub->player.pos.x + cub->render_distance * r.raydirX;
		r.hit_pos.y = cub->player.pos.y + cub->render_distance * r.raydirY;
		draw_line(cub, cub->player.pos, r.hit_pos);
		mlx_put_pixel(cub->minimap, (int)(r.hit_pos.x * cub->mini_ratio), (int)(r.hit_pos.y * cub->mini_ratio), 0xFFFFFFFF);
	}
}



