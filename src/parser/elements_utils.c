#include "cub3d.h"

void	north_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.north_wall = mlx_load_png(path);
}

void	south_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.south_wall = mlx_load_png(path);
}

void	east_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.east_wall = mlx_load_png(path);
}

void	west_parse(t_elements *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.west_wall = mlx_load_png(path);
}
