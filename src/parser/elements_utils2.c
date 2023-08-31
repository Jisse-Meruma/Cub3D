/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:23:12 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:23:12 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	ceiling_parse(t_elements *element, char *path)
{
	char		**p_arr;
	uint32_t	col;

	p_arr = ft_split(path, ',');
	if (!p_arr && ft_2d_arrlen(p_arr) != 3)
		return (ft_2dfree(p_arr), false);
	col = get_rgba(ft_atoi(p_arr[0]),
			ft_atoi(p_arr[1]), ft_atoi(p_arr[2]), 255);
	element->col_ceiling = col;
	ft_2dfree(p_arr);
	return (true);
}

bool	floor_parse(t_elements *element, char *path)
{
	char		**p_arr;
	uint32_t	col;

	p_arr = ft_split(path, ',');
	if (!p_arr && ft_2d_arrlen(p_arr) != 3)
		return (ft_2dfree(p_arr), false);
	col = get_rgba(ft_atoi(p_arr[0]),
			ft_atoi(p_arr[1]), ft_atoi(p_arr[2]), 255);
	element->col_floor = col;
	ft_2dfree(p_arr);
	return (true);
}
