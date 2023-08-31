/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:09:46 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 13:09:47 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <MLX42.h>
# include <struct.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT 900

// Parser functions
bool			parser(char *map_config, t_cubed *cub);
bool			map_extension_check(char *map_path);
bool			open_map(char *map_path, int *fd);
bool			read_map(int file, t_map *map);
bool			setup_map(t_cubed *cub);
bool			validate_map(t_cubed *cub);
void			set_map_tiles(t_map *map);
bool			check_element_order(char **str_map);

// Parser setup map
bool			valid_map_char(char c);
bool			valid_map_str(char *str);
int				map_start_index(char **map);
bool			determine_map_height(t_map *map);
bool			determine_map_width(t_map *map);

bool			parse_elements(t_elements *elements, char **str_map);

uint32_t		get_rgba(int r, int g, int b, int a);
void			error_exit(const char *str, t_cubed *cub);

// Parser-Texture_Utils
bool			north_parse(t_elements *texture, char *path);
bool			south_parse(t_elements *texture, char *path);
bool			east_parse(t_elements *texture, char *path);
bool			west_parse(t_elements *texture, char *path);
bool			ceiling_parse(t_elements *element, char *path);
bool			floor_parse(t_elements *element, char *path);

// Cub3d initilization
bool			cub_init(t_cubed *cub);

// Cub3d loop
bool			cub_loop(t_cubed *cub);
void			cub_controls(t_cubed *cub);

// Cub3d functions
t_vec			vec_rotate(t_vec vec, float angle);

// Cub3d cleanup
bool			cub_end(t_cubed *cub);

// Movement
t_vec			get_move_vec(t_cubed *cub);
void			hitbox_check(t_cubed *cub, t_vec pos, t_vec move_vec);
void			update_mouse(double xdelta, double ydelta, void *param);
void			toggle_hook(mlx_key_data_t keydata, void *param);

// Render
void			draw_wall_segment(uint32_t x, t_raycast_info r,
					t_cubed *cub, mlx_texture_t *text);
mlx_texture_t	*get_texture(t_raycast_info *r, t_texture *textures);
void			draw_floor_and_ceiling(t_cubed *cub);
void			render_frame(t_cubed *cub);
t_raycast_info	raycast(t_vec pos, t_vec dir, t_map map);

// Raycast utils
void			set_distance(t_raycast *r);
void			set_hit_position(t_raycast *r, t_vec pos, t_vec raydir);

// Minimap
bool			minimap_init(t_cubed *cub);
void			draw_line(mlx_image_t *img,
					t_vec p1, t_vec p2, unsigned int color);
void			draw_minimap(t_raycast_info r, t_cubed *cub);
void			draw_minimap_player(t_cubed *cub);

// Utils

t_vec			normalize_vec(t_vec vec);

#endif
