
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
} t_tile;

typedef struct s_textures
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
}	t_textures;

typedef struct s_map
{
	char		**str_map;
	t_tile		**map;
	int			height;
	int			width;
	t_textures 	textures;

}	t_map;

#endif
