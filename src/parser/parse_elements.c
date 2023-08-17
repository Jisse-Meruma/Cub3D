#include "cub3d.h"

t_element	string_to_element(char *str)
{
	if (!ft_strncmp(str, "NO", 3))
		return (NORTH);
	if (!ft_strncmp(str, "SO", 3))
		return (SOUTH);
	if (!ft_strncmp(str, "WE", 3))
		return (WEST);
	if (!ft_strncmp(str, "EA", 3))
		return (EAST);
	if (!ft_strncmp(str, "F", 2))
		return (FLOOR_COL);
	if (!ft_strncmp(str, "C", 2))
		return (CEILING_COL);
	return (NO_VALUE);
}

t_func	select_element(t_element element)
{
	const t_func	functions[7] = {
	[WEST] = west_parse,
	[EAST] = east_parse,
	[NORTH] = north_parse,
	[SOUTH] = south_parse,
	[FLOOR_COL] = floor_parse,
	[CEILING_COL] = ceiling_parse,
	};

	return (functions[element]);
}

bool	parse_elements(t_elements *elements, char **str_map)
{
	char			**arr;
	size_t			index;
	t_func			function;
	t_element		element;

	index = 0;
	while (str_map[index] != NULL)
	{

		arr = ft_split(str_map[index], ' ');
		if (!arr)
			return (false);
		element = string_to_element(arr[0]);
		if (element != NO_VALUE)
		{
			function = select_element(element);
			if(!function(elements, arr[1]))
				return (ft_2dfree(arr), false);
		}
		ft_2dfree(arr);
		index++;
	}
	return (true);
}
