
#ifndef SOOMANYSTRUCTS_H
# define SOOMANYSTRUCTS_H

typedef enum e_tile
{
	SPACE,
	FLOOR,
	WALL,
	PNORTH,
	PEAST,
	PSOUTH,
	PWEST,
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
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
}	t_elements;

typedef struct s_map
{
	char		**str_map;
	t_tile		**map;
	int			height;
	int			width;
	t_elements 	elements;

}	t_map;

typedef struct s_vect
{
	float	x;
	float	y;
} t_vec;
typedef struct s_player
{
	t_vec	dir;
	t_vec	pos;
	t_vec	c_plane;
}	t_player;

typedef struct s_cubed
{
	t_player	*player;
	t_map		*map;
	mlx_t		*mlx;
}	t_cubed;

typedef void (*t_func) (t_elements *, char *);

#endif
