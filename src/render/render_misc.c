#include <cub3d.h>
#include <math.h>

mlx_texture_t	*get_texture(t_raycast *r, t_texture *textures)
{
	if (r->side == 1 && r->raydiry > 0)
		return (textures->north_wall);
	if (r->side == 0 && r->raydirx > 0)
		return (textures->east_wall);
	if (r->side == 1 && r->raydiry < 0)
		return (textures->south_wall);
	if (r->side == 0 && r->raydirx < 0)
		return (textures->west_wall);
	return (NULL);
}

bool	in_image(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x > 0 && x < img->width && y > 0 && y < img->height);
}

void	draw_line(mlx_image_t *img, t_vec cur, t_vec end, unsigned int color)
{
	int		dx;
	int		dy;

	dx = (int)(end.x) - (int)(cur.x);
	dy = (int)(end.y) - (int)(cur.y);
	if (abs(dx) > abs(dy))
	{
		while ((int)cur.x != (int)(end.x) && in_image(img, cur.x, cur.y))
		{
			mlx_put_pixel(img, round(cur.x), round(cur.y), color);
			cur.y += (float)dy / abs(dx);
			cur.x += (float)dx / abs(dx);
		}
	}
	else
	{
		while ((int)cur.y != (int)(end.y) && in_image(img, cur.x, cur.y))
		{
			mlx_put_pixel(img, round(cur.x), round(cur.y), color);
			cur.y += (float)dy / abs(dy);
			cur.x += (float)dx / abs(dy);
		}
	}
}
