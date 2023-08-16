#include <cub3d.h>

static void	add_right_vec(t_vec *move_vec, t_cubed *cub)
{
	move_vec->x += vec_rotate(cub->player.dir, 90).x
		* cub->mlx->delta_time * cub->player.move_speed;
	move_vec->y += vec_rotate(cub->player.dir, 90).y
		* cub->mlx->delta_time * cub->player.move_speed;
}

static void	add_left_vec(t_vec *move_vec, t_cubed *cub)
{
	move_vec->x -= vec_rotate(cub->player.dir, 90).x
		* cub->mlx->delta_time * cub->player.move_speed;
	move_vec->y -= vec_rotate(cub->player.dir, 90).y
		* cub->mlx->delta_time * cub->player.move_speed;
}

static void	add_backward_vec(t_vec *move_vec, t_cubed *cub)
{
	move_vec->x -= cub->player.dir.x
		* cub->mlx->delta_time * cub->player.move_speed;
	move_vec->y -= cub->player.dir.y
		* cub->mlx->delta_time * cub->player.move_speed;
}

static void	add_forward_vec(t_vec *move_vec, t_cubed *cub)
{
	move_vec->x += cub->player.dir.x
		* cub->mlx->delta_time * cub->player.move_speed;
	move_vec->y += cub->player.dir.y
		* cub->mlx->delta_time * cub->player.move_speed;
}

t_vec	get_move_vec(t_cubed *cub)
{
	t_vec	move_vec;

	move_vec.x = 0;
	move_vec.y = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		add_forward_vec(&move_vec, cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		add_backward_vec(&move_vec, cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		add_right_vec(&move_vec, cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		add_left_vec(&move_vec, cub);
	return (move_vec);
}
