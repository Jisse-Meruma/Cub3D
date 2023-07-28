#include "libft.h"
#include <cub3d.h>
#include <stdbool.h>

bool	cub_end(t_cubed *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	mlx_delete_image(cub->mlx, cub->minimap);
	mlx_delete_image(cub->mlx, cub->minimap_view);
	mlx_delete_image(cub->mlx, cub->minimap_explored);
	mlx_delete_image(cub->mlx, cub->minimap_background);
	ft_2dfree(cub->map.str_map);
	ft_2dfree((char **)cub->map.map);
	return (true);
}
