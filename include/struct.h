#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_texture
{
	mlx_texture_t	*north_wall;
	mlx_texture_t	*south_wall;
	mlx_texture_t	*west_wall;
	mlx_texture_t	*east_wall;
}	t_texture;

typedef struct s_elements
{
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	t_texture	texture;
	uint32_t	col_floor;
	uint32_t	col_ceiling;
}	t_elements;

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_map
{
	char		**str_map;
	t_tile		**tiles;
	int			px;
	int			py;
	int			height;
	int			width;
	t_elements	elements;

}	t_map;

typedef struct s_draw_segment
{
	double	wallx;
	int		texx;
	int		texy;
	int		lh;
	int		start;
	int		end;
}	t_draw_segment;

typedef struct s_raycast_info
{
	t_vec	dir;
	t_vec	start;
	t_vec	hit_pos;
	int		side;
	float	perpwalldist;
}	t_raycast_info;

typedef struct s_raycast
{
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	float	sidedistx;
	float	sidedisty;
	float	deltadistx;
	float	deltadisty;
	float	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	t_vec	hit_pos;
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
	mlx_image_t	*minimap_view;
	mlx_image_t	*minimap_explored;
	mlx_image_t	*minimap_background;
	float		mini_ratio;
	float		fov;
	float		render_distance;
	double		prev_mousey;
	double		prev_mousex;
	int			mouse_controls;
}	t_cubed;

typedef bool	(*t_func) (t_elements *, char *);

#endif // STRUCT_H
