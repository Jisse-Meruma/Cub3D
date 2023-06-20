#include "cub3d.h"

void north_parse(t_textures *texture, char *path)
{
	texture->north_texture_path = path;
}

void south_parse(t_textures *texture, char *path)
{
	texture->south_texture_path = path;
}

void east_parse(t_textures *texture, char *path)
{
	texture->east_texture_path = path;
}

void west_parse(t_textures *texture, char *path)
{
	texture->west_texture_path = path;
}