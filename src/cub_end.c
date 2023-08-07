#include "MLX42.h"
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
	mlx_delete_texture(cub->map.elements.texture.east_wall);
	mlx_delete_texture(cub->map.elements.texture.west_wall);
	mlx_delete_texture(cub->map.elements.texture.north_wall);
	mlx_delete_texture(cub->map.elements.texture.south_wall);
	ft_2dfree(cub->map.str_map);
	ft_2dfree((char **)cub->map.map);
	return (true);
}
