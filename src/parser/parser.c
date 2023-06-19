#include "cub3d.h"

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
}