#include "struct.h"
#include <cub3d.h>
#include <stdbool.h>
# define EXTENSION_LENGTH 4

bool	map_extension_check(char *map_path)
{
	if (!map_path && ft_strlen(map_path) >= EXTENSION_LENGTH)
		return (false);
	if (ft_strncmp(map_path + ft_strlen(map_path) - EXTENSION_LENGTH, ".cub", 5))
		return (false);
	return (true);
}

bool	open_map(char *map_path, int *fd)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	read_map(int file, t_map *map)
{
	char	*line;
	char	**str_map;
	char	**temp;

	line = get_next_line(file);
	str_map = ft_2d_add(NULL, line);
	if (!str_map)
		return (false);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		if (!line)
			break ;
		temp = str_map;
		str_map = ft_2d_add(str_map, line);
		ft_2dfree(temp);
		if (!str_map)
			return (free(line), false);
	}
	map->str_map = str_map;
	return (true);
}

bool	flood_fill_validate(t_map *map, int y, int x)
{
	bool	ret;

	ret = true;
	if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1 || map->map[y][x] == SPACE)
		return (false);
	map->map[y][x] = TEMP;
	if (x > 0 && map->map[y][x - 1] != WALL && map->map[y][x - 1] != TEMP)
		ret = flood_fill_validate(map, y, x - 1);
	if (ret && x < map->width && map->map[y][x + 1] != WALL && map->map[y][x + 1] != TEMP)
		ret = flood_fill_validate(map, y, x + 1);
	if (ret && y > 0 && map->map[y - 1][x] != WALL && map->map[y - 1][x] != TEMP)
		ret = flood_fill_validate(map, y - 1, x);
	if (ret && y < map->height && map->map[y + 1][x] != WALL && map->map[y + 1][x] != TEMP)
		ret = flood_fill_validate(map, y + 1, x);
	return (ret);
}

bool	validate_map(t_map *map)
{
	t_tile	p_tile;
	if (map->px == -1)
		return (false);
	p_tile = map->map[map->py][map->px];
	if (!flood_fill_validate(map, map->py, map->px))
		return (false);
	set_map_tiles(map);
	map->map[map->py][map->px] = p_tile;
	return (true);
}
