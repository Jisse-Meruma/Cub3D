#include "cub3d.h"

t_directions	string_to_direction(char *str)
{
	if (!ft_strncmp(str, "NO", 3))
		return (NORTH);
	if (!ft_strncmp(str, "SO", 3))
		return (SOUTH);
	if (!ft_strncmp(str, "WE", 3))
		return (WEST);
	if (!ft_strncmp(str, "EA", 3))
		return (EAST);
	return (NO_DIRECTION);
}

t_func	select_direction(t_directions direction)
{
	const t_func functions[5] = {
	[NORTH] = north_parse,
	[SOUTH] = south_parse,
	[WEST] = west_parse,
	[EAST] = east_parse,
	};

	return (functions[direction]);
}

void	parse_textures(t_textures *textures, char **str_map)
{
	char			**arr;
	size_t 			index;
	t_func 			function;
	t_directions	direction;

	index = 0;
	while (str_map[index] != NULL)
	{
		arr = ft_split(str_map[index], ' ');
		if (!arr)
			return ;
		direction = string_to_direction(arr[0]);
		if (direction != NO_DIRECTION)
		{
			function = select_direction(direction);
			function(textures, arr[1]);
		}
		ft_2dfree(arr);
		index++;
	}
}
