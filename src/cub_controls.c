#include <cub3d.h>

static void	update_player_direction(t_cubed *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player.dir = vec_rotate(cub->player.dir,
				cub->mlx->delta_time * cub->player.turn_speed);
		cub->player.c_plane = vec_rotate(cub->player.c_plane,
				cub->mlx->delta_time * cub->player.turn_speed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player.dir = vec_rotate(cub->player.dir,
				cub->mlx->delta_time * -cub->player.turn_speed);
		cub->player.c_plane = vec_rotate(cub->player.c_plane,
				cub->mlx->delta_time * -cub->player.turn_speed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		cub->player.head_pitch += cub->mlx->delta_time * 300;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		cub->player.head_pitch -= cub->mlx->delta_time * 300;
}

void	cub_movement_check(t_cubed *cub)
{
	t_vec	move_vec;

	move_vec = get_move_vec(cub);
	if (cub->map.map[(int)(cub->player.pos.y)]
		[(int)(cub->player.pos.x + (move_vec.x * 3.0))] == 1)
	{
		cub->player.pos.x += move_vec.x;
	}
	if (cub->map.map[(int)(cub->player.pos.y + (move_vec.y * 3.0))]
		[(int)(cub->player.pos.x)] == 1)
		cub->player.pos.y += move_vec.y;
}

void	cub_controls(t_cubed *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
	}
	update_player_direction(cub);
	cub_movement_check(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_EQUAL))
		cub->fov += 0.1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_MINUS))
		cub->fov -= 0.1;
}
