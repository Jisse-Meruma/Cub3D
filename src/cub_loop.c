#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>

void	draw_tile(int x, int y, unsigned int tile_scale, mlx_image_t *img, unsigned int color)
{
	unsigned int	dx;
	unsigned int	dy;

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

t_vec	cub_get_move_vec(t_cubed *cub)
{
	t_vec	move_vec;

	move_vec.x = 0;
	move_vec.y = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		move_vec.x += cub->player.dir.x * cub->mlx->delta_time * cub->player.move_speed;
		move_vec.y += cub->player.dir.y * cub->mlx->delta_time * cub->player.move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		move_vec.x -= cub->player.dir.x * cub->mlx->delta_time * cub->player.move_speed;
		move_vec.y -= cub->player.dir.y * cub->mlx->delta_time * cub->player.move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		move_vec.x += vec_rotate(cub->player.dir, -90).x * cub->mlx->delta_time * cub->player.move_speed;
		move_vec.y += vec_rotate(cub->player.dir, -90).y * cub->mlx->delta_time * cub->player.move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		move_vec.x -= vec_rotate(cub->player.dir, -90).x * cub->mlx->delta_time * cub->player.move_speed;
		move_vec.y -= vec_rotate(cub->player.dir, -90).y * cub->mlx->delta_time * cub->player.move_speed;
	}
	return (move_vec);
}

void	cub_movement_check(t_cubed *cub)
{
	t_vec	move_vec;

	move_vec = cub_get_move_vec(cub);
	if (cub->map.map[(int)(cub->player.pos.y + move_vec.y)][(int)(cub->player.pos.x + move_vec.x)] == 1)
	{
		cub->player.pos.x += move_vec.x;
		cub->player.pos.y += move_vec.y;
	}
}

void	cub_controls(t_cubed *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player.dir = vec_rotate(cub->player.dir, cub->mlx->delta_time * -cub->player.turn_speed);
		cub->player.c_plane = vec_rotate(cub->player.c_plane, cub->mlx->delta_time * -cub->player.turn_speed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player.dir = vec_rotate(cub->player.dir,cub->mlx->delta_time * cub->player.turn_speed);
		cub->player.c_plane = vec_rotate(cub->player.c_plane, cub->mlx->delta_time * cub->player.turn_speed);
	}
	cub_movement_check(cub);
}

void	cub_frame(void *param)
{
	t_cubed	*cub;

	cub = (t_cubed *)param;
	 //draw_map(cub);
	cub_controls(cub);
	ft_bzero(cub->img->pixels, (cub->img->width * cub->img->height) * 8);
	raycast(cub);
	// printf("1\n");
}

bool	cub_loop(t_cubed *cub)
{
	if (!mlx_loop_hook(cub->mlx, cub_frame, (void *)cub))
		return (false);
	usleep(100);
	mlx_loop(cub->mlx);
	return (true);
}
