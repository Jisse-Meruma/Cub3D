/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:03 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 13:52:51 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static bool	minimap_images_init(t_cubed *cub)
{
	int	x_size;
	int	y_size;

	x_size = (int)(cub->mini_ratio * cub->map.width);
	y_size = (int)(cub->mini_ratio * cub->map.height);
	cub->minimap = mlx_new_image(cub->mlx, x_size, y_size);
	cub->minimap_view = mlx_new_image(cub->mlx, x_size, y_size);
	cub->minimap_explored = mlx_new_image(cub->mlx, x_size, y_size);
	cub->minimap_background = mlx_new_image(cub->mlx, x_size, y_size);
	if (!cub->minimap_background || !cub->minimap
		|| !cub->minimap_view || !cub->minimap_explored)
		return (false);
	return (true);
}

bool	minimap_init(t_cubed *cub)
{
	int	mini_scale;

	if (WINDOW_WIDTH > WINDOW_HEIGHT)
		mini_scale = WINDOW_WIDTH / 4;
	else
		mini_scale = WINDOW_HEIGHT / 4;
	if (cub->map.width > cub->map.height)
		cub->mini_ratio = (float)mini_scale / (float)cub->map.width;
	else
		cub->mini_ratio = (float)mini_scale / (float)cub->map.height;
	if (!minimap_images_init(cub))
		return (false);
	draw_minimap_background(cub);
	return (true);
}
