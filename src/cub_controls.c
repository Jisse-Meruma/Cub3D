#include <cub3d.h>
#include <math.h>

void	update_mouse(double xpos, double ypos, void *param)
{
	t_cubed	*cub;

	cub = (t_cubed *)param;
	cub->player.dir = vec_rotate(cub->player.dir,
			(cub->mlx->delta_time * (xpos - cub->prev_mousex)
				* cub->player.turn_speed) / 8);
	cub->player.c_plane = vec_rotate(cub->player.c_plane,
			(cub->mlx->delta_time * (xpos - cub->prev_mousex)
				* cub->player.turn_speed) / 8);
	cub->player.head_pitch -= cub->mlx->delta_time
		* (ypos - cub->prev_mousey) * 150;
	if (cub->player.head_pitch > (int)(cub->img->height / 2))
		cub->player.head_pitch = (int)(cub->img->height / 2);
	else if (cub->player.head_pitch < -(int)(cub->img->height / 2))
		cub->player.head_pitch = -(int)(cub->img->height / 2);
	cub->prev_mousey = cub->img->height / 2;
	cub->prev_mousex = cub->img->width / 2;
	mlx_set_mouse_pos(cub->mlx, cub->img->width / 2, cub->img->height / 2);
}

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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP)
		&& cub->player.head_pitch < (int)(cub->img->height / 2))
		cub->player.head_pitch += cub->mlx->delta_time * 300;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)
		&& cub->player.head_pitch > -(int)(cub->img->height / 2))
		cub->player.head_pitch -= cub->mlx->delta_time * 300;
}

static t_vec	normalize_vec(t_vec vec)
{
	float	a;
	float	b;
	float	c;

	a = vec.x * vec.x;
	b = vec.y * vec.y;
	c = sqrt(a + b);
	vec.x = vec.x / c;
	vec.y = vec.y / c;
	return (vec);
}

void	cub_movement_check(t_cubed *cub)
{
	t_vec			move_vec;
	t_raycast_info	r;

	move_vec = get_move_vec(cub);
	if (move_vec.x == 0 && move_vec.y == 0)
		return ;
	move_vec = normalize_vec(move_vec);
	r = raycast(cub->player.pos, move_vec, cub->map);
	printf("pos: %f, %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("Before: %f, %f\n", move_vec.x, move_vec.y);
	if (r.perpwalldist < cub->mlx->delta_time * cub->player.move_speed)
	{
		move_vec.x = move_vec.x * r.perpwalldist;
		move_vec.y = move_vec.y * r.perpwalldist;
	}
	else if (r.perpwalldist > cub->mlx->delta_time * cub->player.move_speed)
	{
		move_vec.x = move_vec.x * cub->mlx->delta_time * cub->player.move_speed;
		move_vec.y = move_vec.y * cub->mlx->delta_time * cub->player.move_speed;
	}
	printf("move_vec: %f, %f\n", move_vec.x, move_vec.y);
	printf("perpwalldist: %f, move speed: %f\n", r.perpwalldist, cub->mlx->delta_time * cub->player.move_speed);
	if (fabsf(move_vec.x) < 0.2)
		move_vec.x = 0;
	if (fabsf(move_vec.y) < 0.2)
		move_vec.y = 0;
	if (cub->map.tiles[(int)cub->player.pos.y][(int)(cub->player.pos.x + move_vec.x)] != WALL)
		cub->player.pos.x += move_vec.x;
	if (cub->map.tiles[(int)(cub->player.pos.y + move_vec.y)][(int)cub->player.pos.x] != WALL)
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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_EQUAL) && cub->fov < 10)
		cub->fov += 0.1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_MINUS) && cub->fov > 0.5)
		cub->fov -= 0.1;
}
