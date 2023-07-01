#include "libft.h"
#include <cub3d.h>
#include <stdbool.h>

bool	cub_end(t_cubed *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	ft_2dfree(cub->map.str_map);
	ft_2dfree((char **)cub->map.map);
	free(cub->map.elements.west_texture_path);
	free(cub->map.elements.east_texture_path);
	free(cub->map.elements.north_texture_path);
	free(cub->map.elements.south_texture_path);
	return (true);
}
