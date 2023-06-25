#include <cub3d.h>

bool	player_init(t_cubed *cub)
{
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
	return (true);
}
