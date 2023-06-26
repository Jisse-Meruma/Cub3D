#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>

void	draw_tile(int x, int y, int tile_scale, mlx_image_t *img, unsigned int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < tile_scale)
	{
		dx = 0;
		while (dx < tile_scale)
		{
			if (dx < img->width && dy < img->height)
				mlx_put_pixel(img, dx + (x * tile_scale), dy + (y * tile_scale), color);
			dx++;
		}
		dy++;
	}
}

void	draw_map(t_cubed *cub)
{
	int	y;
	int	x;
	int	tile_scale;

	tile_scale = 50;
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (cub->map.map[y][x] == WALL)
				draw_tile(x, y, tile_scale, cub->img, 0x777777FF);
			if (cub->map.map[y][x] == FLOOR)
				draw_tile(x, y, tile_scale, cub->img, 0x444444FF);
			x++;
		}
		y++;
	}
}

void	cub_frame(void *param)
{
	t_cubed	*cub;

	cub = (t_cubed *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
	}
	draw_map(cub);
}

bool	cub_loop(t_cubed *cub)
{
	if (!mlx_loop_hook(cub->mlx, cub_frame, (void *)cub))
		return (false);
	mlx_loop(cub->mlx);
	return (true);
}
