
#ifndef SOOMANYSTRUCTS_H
# define SOOMANYSTRUCTS_H

# include <MLX42.h>

typedef enum e_tile
{
	SPACE,
	FLOOR,
	WALL,
	PNORTH,
	PEAST,
	PSOUTH,
	PWEST,
	TEMP,
}	t_tile;

typedef enum e_element
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR_COL,
	CEILING_COL,
	NO_VALUE,
}	t_element;

typedef struct s_elements
{
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	uint32_t	col_floor;
	uint32_t	col_ceiling;
}	t_elements;

typedef struct s_vect
{
	float	x;
	float	y;
} t_vec;

typedef struct s_map
{
	char		**str_map;
	t_tile		**map;
	int			px;
	int			py;
	int			height;
	int			width;
	t_elements 	elements;

}	t_map;

typedef struct	s_raycast
{
	double	camx;
	double	raydirX;
	double	raydirY;
	int		mapX;
	int		mapY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	float	perpWallDist;
	double	wallX;
	t_vec	hit_pos;
	int		texX;
	float	realWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
}	t_raycast;

typedef struct s_player
{
	t_vec	dir;
	t_vec	pos;
	t_vec	c_plane;
	float	move_speed;
	float	turn_speed;
	int		head_pitch;
}	t_player;

typedef struct s_cubed
{
	t_player	player;
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap;
	mlx_image_t	*minimap_explored;
	mlx_image_t	*minimap_background;
	float		mini_ratio;
	float		fov;
	float		render_distance;
}	t_cubed;

typedef void (*t_func) (t_elements *, char *);

#endif
