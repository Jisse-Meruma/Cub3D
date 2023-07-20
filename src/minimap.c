# include <cub3d.h>

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

	while (x != p2.x * cub->mini_ratio && y != p2.y * cub->mini_ratio)
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
			x++;
		}
	}
}


