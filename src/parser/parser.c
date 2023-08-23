#include <cub3d.h>

bool	parser(char *map_config, t_cubed *cub)
{
	int	file;

	if (!map_extension_check(map_config))
		return (error_exit("Invalid Map Extension]\n", cub), false);
	if (!open_map(map_config, &file))
		return (error_exit("Cant Open Map\n", cub), false);
	if (!read_map(file, &cub->map))
		return (error_exit("Map Reading Allocation Failed\n", cub), false);
	if (!check_element_order(cub->map.str_map))
		return (error_exit("Map is not the last element!\n", cub), false);
	if (!parse_elements(&(cub->map.elements), cub->map.str_map))
		return (error_exit("Parse Elements Allocation Failed\n", cub), false);
	if (!setup_map(cub))
		return (false);
	if (!validate_map(cub))
		return (false);
	return (true);
}
