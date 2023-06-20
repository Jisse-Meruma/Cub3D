#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <MLX42.h>
# include <struct.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

bool	parser(char *map_config, t_map *map);
bool	map_extension_check(char *map_path);
bool	open_map(char *map_path, int *fd);
bool	read_map(int file, t_map *map);
bool	setup_map(t_map *map);

// Parser-Texture_Utils
void north_parse(t_textures *texture, char *path);
void south_parse(t_textures *texture, char *path);
void east_parse(t_textures *texture, char *path);
void west_parse(t_textures *texture, char *path);


#endif
