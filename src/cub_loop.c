#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>
#include <stdint.h>

// void	draw_tile(int x, int y, unsigned int tile_scale, mlx_image_t *img,
// unsigned int color)
// {
// 	unsigned int	dx;
// 	unsigned int	dy;
//
// 	dy = 0;
// 	while (dy < tile_scale)
// 	{
// 		dx = 0;
// 		while (dx < tile_scale)
// 		{
// 			if (dx < img->width && dy < img->height)
// 				mlx_put_pixel(img, dx + (x * tile_scale),
//					dy + (y * tile_scale), color);
// 			dx++;
// 		}
// 		dy++;
// 	}
// }

// void	draw_map(t_cubed *cub)
// {
// 	int	y;
// 	int	x;
// 	int	tile_scale;
//
// 	tile_scale = 10;
// 	y = 0;
// 	while (y < cub->map.height)
// 	{
// 		x = 0;
// 		while (x < cub->map.width)
// 		{
// 			if (cub->map.map[y][x] == WALL)
// 				draw_tile(x, y, tile_scale, cub->img, 0x777777FF);
// 			if (cub->map.map[y][x] == FLOOR)
// 				draw_tile(x, y, tile_scale, cub->img, 0x444444FF);
// 			x++;
// 		}
// 		y++;
// 	}
// }

bool	cub_update_image_scale(t_cubed *cub)
{
	if ((uint32_t)cub->mlx->width != cub->img->width
		|| (uint32_t)cub->mlx->height != cub->img->height)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
		mlx_image_to_window(cub->mlx, cub->img, 0, 0);
		cub->img->instances[0].z = 0;
		return (true);
	}
	return (false);
}

void	draw_floor_and_ceiling(t_cubed *cub)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < cub->img->height)
	{
		x = 0;
		while (x < cub->img->width)
		{
			if (y < cub->img->height / 2 + cub->player.head_pitch)
				mlx_put_pixel(cub->img, x, y, cub->map.elements.col_ceiling);
			else
				mlx_put_pixel(cub->img, x, y, cub->map.elements.col_floor);
			x++;
		}
		y++;
	}
}

void	cub_frame(void *param)
{
	t_cubed	*cub;

	cub = (t_cubed *)param;
	if (cub_update_image_scale(cub))
		return ;
	cub_controls(cub);
	ft_bzero(cub->img->pixels, (cub->img->width * cub->img->height) * 4);
	draw_floor_and_ceiling(cub);
	raycast(cub);
}

bool	cub_loop(t_cubed *cub)
{
	if (!mlx_loop_hook(cub->mlx, cub_frame, (void *)cub))
		return (error_exit("Mlx Loop hook failed\n", cub), false);
	mlx_loop(cub->mlx);
	return (true);
}
