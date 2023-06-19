#include "cub3d.h"
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
