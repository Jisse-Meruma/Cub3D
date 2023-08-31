/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:18 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:22:24 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "struct.h"
#include <cub3d.h>
#include <stdint.h>

bool	cub_update_image_scale(t_cubed *cub)
{
	if ((uint32_t)cub->mlx->width != cub->img->width
		|| (uint32_t)cub->mlx->height != cub->img->height)
	{
		mlx_delete_image(cub->mlx, cub->img);
		cub->img = mlx_new_image(cub->mlx, cub->mlx->width, cub->mlx->height);
		mlx_image_to_window(cub->mlx, cub->img, 0, 0);
		cub->img->instances[0].z = 0;
		return (true);
	}
	return (false);
}

void	cub_tick(void *param)
{
	t_cubed	*cub;

	cub = (t_cubed *)param;
	if (cub_update_image_scale(cub))
		return ;
	cub_controls(cub);
	render_frame(cub);
}

bool	cub_loop(t_cubed *cub)
{
	if (!mlx_loop_hook(cub->mlx, cub_tick, (void *)cub))
		return (error_exit("Mlx Loop hook failed\n", cub), false);
	mlx_cursor_hook(cub->mlx, update_mouse, (void *)cub);
	mlx_key_hook(cub->mlx, toggle_hook, (void *)cub);
	mlx_loop(cub->mlx);
	return (true);
}
