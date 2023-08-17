#include "cub3d.h"

bool	north_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.north_wall = mlx_load_png(path);
	if (!texture->texture.north_wall)
		return (false);
	return (true);

}

bool	south_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.south_wall = mlx_load_png(path);
	if (!texture->texture.south_wall)
		return (false);
	return (true);

}

bool	east_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.east_wall = mlx_load_png(path);
	if (!texture->texture.east_wall)
		return (false);
	return (true);

}

bool	west_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.west_wall = mlx_load_png(path);
	if (!texture->texture.west_wall)
		return (false);
	return (true);

}
