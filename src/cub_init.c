#include <cub3d.h>
#include <stdbool.h>
#include <stdint.h>

void	get_player_orientation(t_cubed *cub)
{
	
	if (cub->map.map[cub->map.py][cub->map.px] == PNORTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
	}
	else if (cub->map.map[cub->map.py][cub->map.px] == PEAST)
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
	}
	else if (cub->map.map[cub->map.py][cub->map.px] == PSOUTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
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
	cub->map.map[cub->map.py][cub->map.px] = FLOOR;
	cub->player.c_plane = vec_rotate(cub->player.dir, 90);
	cub->player.move_speed = 5;
	cub->player.turn_speed = 200;
	cub->player.head_pitch = 0;
	printf("init playerdirXY: %f, %f\ninit c_planeXY: %f, %f\n", cub->player.dir.x, cub->player.dir.y, cub->player.c_plane.x, cub->player.c_plane.y);
	return (true);
}

void	draw_minimap_background(t_cubed *cub)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < cub->minimap_background->height)
	{
		x = 0;
		while (x < cub->minimap_background->width)
		{
			mlx_put_pixel(cub->minimap_background, x, y, 0x555555DD);
			x++;
		}
		y++;
	}
}

bool	minimap_init(t_cubed *cub)
{
	int	mini_scale;

	if (WINDOW_WIDTH > WINDOW_HEIGHT)
		mini_scale = WINDOW_WIDTH / 4;
	else
		mini_scale = WINDOW_HEIGHT / 4;
	cub->minimap = mlx_new_image(cub->mlx, mini_scale, mini_scale);
	cub->minimap_view = mlx_new_image(cub->mlx, mini_scale, mini_scale);
	cub->minimap_explored = mlx_new_image(cub->mlx, mini_scale, mini_scale);
	cub->minimap_background = mlx_new_image(cub->mlx, mini_scale, mini_scale);
	if (!cub->minimap_background || !cub->minimap || !cub->minimap_view || !cub->minimap_explored)
	{
		mlx_delete_image(cub->mlx, cub->minimap);
		mlx_delete_image(cub->mlx, cub->minimap_view);
		mlx_delete_image(cub->mlx, cub->minimap_explored);
		mlx_delete_image(cub->mlx, cub->minimap_background);
		return (false);
	}
	draw_minimap_background(cub);
	if (cub->map.width > cub->map.height)
		cub->mini_ratio = (float)cub->minimap->width / (float)cub->map.width;	
	else
		cub->mini_ratio = (float)cub->minimap->height / (float)cub->map.height;
	return (true);
}

bool	init_images(t_cubed *cub)
{


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
	if (!minimap_init(cub))
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->minimap, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->minimap_view, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->minimap_explored, 0, 0) == -1)
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->minimap_background, 0, 0) == -1)
		return (false);
	cub->minimap->instances[0].z = 3;
	cub->minimap_view->instances[0].z = 4;
	cub->minimap_background->instances[0].z = 1;
	cub->minimap_explored->instances[0].z = 2;
	cub->fov = 3.0;
	cub->render_distance = 10;
	cub->map.map[cub->map.py][cub->map.px] = FLOOR;
	return (true);
}
