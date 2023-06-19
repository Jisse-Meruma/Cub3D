#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "struct.h"
# include <stdbool.h>
# include <fcntl.h>

bool	parser(char *map_config, t_map *map);
bool	map_extension_check(char *map_path);
bool	open_map(char *map_path, int *fd);




#endif