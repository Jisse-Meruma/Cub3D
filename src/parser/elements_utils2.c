#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ceiling_parse(t_elements *element, char *path)
{
	char		**p_arr;
	uint32_t	col;

	p_arr = ft_split(path, ',');
	if (!p_arr && ft_2d_arrlen(p_arr) != 3)
		return (ft_2dfree(p_arr));
	col = get_rgba(ft_atoi(p_arr[0]),
			ft_atoi(p_arr[1]), ft_atoi(p_arr[2]), 255);
	element->col_ceiling = col;
	ft_2dfree(p_arr);
}

void	floor_parse(t_elements *element, char *path)
{
	char		**p_arr;
	uint32_t	col;

	p_arr = ft_split(path, ',');
	if (!p_arr && ft_2d_arrlen(p_arr) != 3)
		return (ft_2dfree(p_arr));
	col = get_rgba(ft_atoi(p_arr[0]),
			ft_atoi(p_arr[1]), ft_atoi(p_arr[2]), 255);
	element->col_floor = col;
	ft_2dfree(p_arr);
}
