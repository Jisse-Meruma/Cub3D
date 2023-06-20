#include <cub3d.h>

static bool	valid_map_char(char c)
{
	return (c == '1' || c == ' ' || c == '0'
		|| c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

static bool	valid_map_str(char *str)
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

static int	map_start_index(char **map)
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

int	determine_map_height(t_map *map)
{
	int	i;
	int	height;

	i = map_start_index(map->str_map);
	printf("start index: %i\n", i);
	height = 0;
	while (map->str_map[i] && map->str_map[i][0] != '\n')
	{
		i++;
		height++;
	}
	return (height);
}

int	determine_map_width(t_map *map)
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
	return (max_width);
}

bool	allocate_map_tiles(t_map *map)
{
	int	i;

	i = 0;
	map->map = ft_calloc(map->height + 1, sizeof(t_tile*));
	if (map->map == NULL)
		return (false);
	while (i < map->height)
	{
		map->map[i] = ft_calloc(map->width + 1, sizeof(t_tile));
		if ((map->map)[i] == NULL)
		{
			ft_2dfree((char **)map->map);
			return (false);
		}
		i++;
	}
	return (true);
}

t_tile	get_tile(char c)
{
	if (c == ' ')
		return (SPACE);
	else if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (PNORTH);
	else if (c == 'E')
		return (PEAST);
	else if (c == 'S')
		return (PSOUTH);
	else
		return (PWEST);

}

bool	set_map_tiles(t_map *map)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = map_start_index(map->str_map);
	while (map->str_map[i] && valid_map_str(map->str_map[i]))
	{
		j = 0;
		while (map->str_map[i][j])
		{
			map->map[y][j] = get_tile(map->str_map[i][j]);
			j++;
		}
		y++;
		i++;
	}
	return (true);
}

bool	setup_map(t_map *map)
{
	map->height = determine_map_height(map);
	map->width = determine_map_width(map);
	if (!allocate_map_tiles(map))
		return (false);
	if (!set_map_tiles(map))
		return (false);
	printf("width: %i, height: %i\n", map->width, map->height);
	return (true);
}
