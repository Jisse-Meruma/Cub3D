/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hitbox_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:06 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:22:06 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	hitbox_check(t_cubed *cub, t_vec pos, t_vec mv)
{
	int	addy;
	int	addx;

	addx = 1;
	addy = 1;
	if (cub->map.tiles[(int)(pos.y + 0.1)][(int)(pos.x + 0.1 + mv.x)] == WALL)
		addx = 0;
	if (cub->map.tiles[(int)(pos.y - 0.1)][(int)(pos.x + 0.1 + mv.x)] == WALL)
		addx = 0;
	if (cub->map.tiles[(int)(pos.y + 0.1)][(int)(pos.x - 0.1 + mv.x)] == WALL)
		addx = 0;
	if (cub->map.tiles[(int)(pos.y - 0.1)][(int)(pos.x - 0.1 + mv.x)] == WALL)
		addx = 0;
	if (cub->map.tiles[(int)(pos.y + 0.1 + mv.y)][(int)(pos.x + 0.1)] == WALL)
		addy = 0;
	if (cub->map.tiles[(int)(pos.y - 0.1 + mv.y)][(int)(pos.x + 0.1)] == WALL)
		addy = 0;
	if (cub->map.tiles[(int)(pos.y + 0.1 + mv.y)][(int)(pos.x - 0.1)] == WALL)
		addy = 0;
	if (cub->map.tiles[(int)(pos.y - 0.1 + mv.y)][(int)(pos.x - 0.1)] == WALL)
		addy = 0;
	if (addy == 1)
		cub->player.pos.y += mv.y;
	if (addx == 1)
		cub->player.pos.x += mv.x;
}
