
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

typedef struct s_map
{
	char	**str_map;
	t_tile	**map;

}	t_map;

#endif 
