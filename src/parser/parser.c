#include <cub3d.h>

void	print_map_str(t_map *map)
{
	int i;

	i = 0;
	while (map->str_map[i])
	{
		printf("%s", map->str_map[i]);
		i++;
	}
}

bool	parser(char *map_config, t_map *map)
{
	int	file;

	if (!map_extension_check(map_config))
	{
		printf("SOMETHING WENT WRONG WITH THE EXTENSION AAAAAA\n");
		return (false);
	}
	if (!open_map(map_config, &file))
	{
		printf("SOMETHING WENT WRONG WITH THE OPENING AAAAAA\n");
		return (false);
	}
	if (!read_map(file, map))
	{
		printf("SOMETHING WENT WRONG WITH READING AAAAAA\n");
		return (false);
	}
	print_map_str(map);
	parse_elements(&(map->elements), map->str_map);
	if (!setup_map(map))
	{
		printf("SOMETHING WENT WRONG WITH MAP SETUP AAAAAA\n");
		return (false);
	}
	return (true);
}
