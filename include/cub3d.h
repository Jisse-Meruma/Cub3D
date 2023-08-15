#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <MLX42.h>
# include <struct.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_WIDTH 720
# define WINDOW_HEIGHT 720

// Parser functions
bool			parser(char *map_config, t_map *map);
bool			map_extension_check(char *map_path);
bool			open_map(char *map_path, int *fd);
bool			read_map(int file, t_map *map);
bool			setup_map(t_map *map);
bool			validate_map(t_map *map);
bool			set_map_tiles(t_map *map);

void			parse_elements(t_elements *elements, char **str_map);

uint32_t		get_rgba(int r, int g, int b, int a);
void			error_exit(const char *str, t_cubed *cub);

// Parser-Texture_Utils
void			north_parse(t_elements *texture, char *path);
void			south_parse(t_elements *texture, char *path);
void			east_parse(t_elements *texture, char *path);
void			west_parse(t_elements *texture, char *path);
void			ceiling_parse(t_elements *element, char *path);
void			floor_parse(t_elements *element, char *path);

// Cub3d initilization
bool			cub_init(t_cubed *cub);

// Cub3d loop
bool			cub_loop(t_cubed *cub);
void			cub_controls(t_cubed *cub);

// Cub3d functions
t_vec			vec_rotate(t_vec vec, float angle);
void			raycast(t_cubed *cub);

// Cub3d cleanup
bool			cub_end(t_cubed *cub);

// Render
void			draw_wall_segment(uint32_t x, t_raycast r,
					t_cubed *cub, mlx_texture_t *text);
mlx_texture_t	*get_texture(t_raycast *r, t_texture *textures);

// Minimap
void			draw_line(mlx_image_t *img,
					t_vec p1, t_vec p2, unsigned int color);
void			draw_minimap(t_raycast r, t_cubed *cub);
void			draw_minimap_player(t_cubed *cub);

#endif
