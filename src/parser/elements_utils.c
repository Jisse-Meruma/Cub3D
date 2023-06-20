#include "cub3d.h"

void north_parse(t_elements *texture, char *path)
{
	texture->north_texture_path = ft_strdup(path);
}

void south_parse(t_elements *texture, char *path)
{
	texture->south_texture_path = ft_strdup(path);
}

void east_parse(t_elements *texture, char *path)
{
	texture->east_texture_path = ft_strdup(path);
}

void west_parse(t_elements *texture, char *path)
{
	texture->west_texture_path = ft_strdup(path);
}