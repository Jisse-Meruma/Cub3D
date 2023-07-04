#include <cub3d.h>

void	get_player_orientation(t_cubed *cub)
{
	
	if (cub->map.map[cub->map.py][cub->map.px] == PNORTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
	}
	else if (cub->map.map[cub->map.py][cub->map.px] == PEAST)
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
	}
	else if (cub->map.map[cub->map.py][cub->map.px] == PSOUTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
	}
	else if (cub->map.map[cub->map.py][cub->map.px] == PWEST)
	{
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
	}
	printf("init playerdirXY: %f, %f\ninit c_planeXY: %f, %f\n", cub->player.dir.x, cub->player.dir.y, cub->player.c_plane.x, cub->player.c_plane.y);

}

bool	player_init(t_cubed *cub)
{
	get_player_orientation(cub);
	cub->player.pos.x = cub->map.px;
	cub->player.pos.y = cub->map.py;
	cub->player.c_plane = vec_rotate(cub->player.dir, -90);
	cub->player.move_speed = 10;
	cub->player.turn_speed = 200;
	printf("init playerdirXY: %f, %f\ninit c_planeXY: %f, %f\n", cub->player.dir.x, cub->player.dir.y, cub->player.c_plane.x, cub->player.c_plane.y);
	return (true);
}


bool	cub_init(t_cubed *cub)
{
	if (!player_init(cub))
		return (false);
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", 1);
	if (cub->mlx == NULL)
		return (false);
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->img)
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (false);
	cub->fov = 3.0;
	cub->render_distance = 10;
	// draw_map(cub);
	return (true);
}
