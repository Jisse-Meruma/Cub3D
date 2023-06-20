#include "cub3d.h"

bool	ft_isspace(int c)
{
	if (c == '\v' || c == '\t' || c == ' ' \
		|| c == '\f' || c == '\r')
		return (true);
	return (false);
}



void	parse_textures(t_textures *textures, char **str_map)
{
	size_t index;

	index = 0;
	while (str_map[index])
	{
	}
}