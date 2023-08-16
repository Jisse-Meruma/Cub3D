#include <cub3d.h>

bool	valid_map_char(char c)
{
	return (c == '1' || c == ' ' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

bool	valid_map_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n')
		return (false);
	while (str[i] && str[i] != '\n')
	{
		if (!valid_map_char(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	map_start_index(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (valid_map_str(map[i]))
			break ;
		i++;
	}
	return (i);
}

bool	determine_map_height(t_map *map)
{
	int	i;
	int	height;

	i = map_start_index(map->str_map);
	height = 0;
	while (map->str_map[i] && map->str_map[i][0] != '\n')
	{
		if (!valid_map_str(map->str_map[i]))
			return (false);
		i++;
		height++;
	}
	map->height = height;
	return (true);
}

bool	determine_map_width(t_map *map)
{
	int	i;
	int	width;
	int	max_width;

	max_width = 0;
	i = map_start_index(map->str_map);
	while (map->str_map[i] && valid_map_str(map->str_map[i]))
	{
		width = ft_strlen(map->str_map[i]) - 1;
		if (width > max_width)
			max_width = width;
		i++;
	}
	map->width = max_width;
	return (true);
}
