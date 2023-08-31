/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_end.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:32 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:22:33 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include <cub3d.h>
#include <stdbool.h>

void	mlx_end(t_cubed *cub)
{
	if (cub->img != NULL)
		mlx_delete_image(cub->mlx, cub->img);
	if (cub->minimap != NULL)
		mlx_delete_image(cub->mlx, cub->minimap);
	if (cub->minimap_view != NULL)
		mlx_delete_image(cub->mlx, cub->minimap_view);
	if (cub->minimap_explored != NULL)
		mlx_delete_image(cub->mlx, cub->minimap_explored);
	if (cub->minimap_background != NULL)
		mlx_delete_image(cub->mlx, cub->minimap_background);
}

bool	cub_end(t_cubed *cub)
{
	if (cub->mlx != NULL)
		mlx_end(cub);
	if (cub->map.elements.texture.east_wall != NULL)
		mlx_delete_texture(cub->map.elements.texture.east_wall);
	if (cub->map.elements.texture.west_wall != NULL)
		mlx_delete_texture(cub->map.elements.texture.west_wall);
	if (cub->map.elements.texture.north_wall != NULL)
		mlx_delete_texture(cub->map.elements.texture.north_wall);
	if (cub->map.elements.texture.south_wall != NULL)
		mlx_delete_texture(cub->map.elements.texture.south_wall);
	ft_2dfree(cub->map.str_map);
	ft_2dfree((char **)cub->map.tiles);
	return (true);
}
