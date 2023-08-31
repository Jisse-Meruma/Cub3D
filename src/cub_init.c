/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:28 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 14:01:13 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>
#include <stdint.h>

void	get_player_orientation(t_cubed *cub)
{
	if (cub->map.tiles[cub->map.py][cub->map.px] == PNORTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
	}
	else if (cub->map.tiles[cub->map.py][cub->map.px] == PEAST)
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
	}
	else if (cub->map.tiles[cub->map.py][cub->map.px] == PSOUTH)
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
	}
	else if (cub->map.tiles[cub->map.py][cub->map.px] == PWEST)
	{
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
	}
}

void	player_init(t_cubed *cub)
{
	get_player_orientation(cub);
	cub->player.pos.x = cub->map.px;
	cub->player.pos.y = cub->map.py;
	cub->map.tiles[cub->map.py][cub->map.px] = FLOOR;
	cub->player.c_plane = vec_rotate(cub->player.dir, 90);
	cub->player.move_speed = 5;
	cub->player.turn_speed = 200;
	cub->player.head_pitch = 0;
}

static bool	image_init(t_cubed *cub)
{
	cub->img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub->img)
		return (false);
	if (!minimap_init(cub))
		return (false);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1
		|| mlx_image_to_window(cub->mlx, cub->minimap, 0, 0) == -1
		|| mlx_image_to_window(cub->mlx, cub->minimap_view, 0, 0) == -1
		|| mlx_image_to_window(cub->mlx, cub->minimap_explored, 0, 0) == -1
		|| mlx_image_to_window(cub->mlx, cub->minimap_background, 0, 0) == -1)
		return (false);
	cub->minimap->instances[0].z = 3;
	cub->minimap_view->instances[0].z = 4;
	cub->minimap_background->instances[0].z = 1;
	cub->minimap_explored->instances[0].z = 2;
	return (true);
}

bool	cub_init(t_cubed *cub)
{
	player_init(cub);
	cub->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", 1);
	if (cub->mlx == NULL)
		return (error_exit("Mlx initilization failed\n", cub), false);
	if (!image_init(cub))
		return (error_exit("Image initilization failed\n", cub), false);
	cub->fov = 3.0;
	cub->render_distance = 10;
	cub->map.tiles[cub->map.py][cub->map.px] = FLOOR;
	return (true);
}
