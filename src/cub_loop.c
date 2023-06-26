#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>

void	draw_map(t_cubed *cub)
{
	
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
