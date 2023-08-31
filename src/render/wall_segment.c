/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wall_segment.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:22:39 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 12:22:40 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

float	get_wall_x(t_cubed *cub, t_raycast_info r)
{
	float	wall_x;

	if (r.side == 0)
		wall_x = cub->player.pos.y + r.perpwalldist * r.dir.y;
	else
		wall_x = cub->player.pos.x + r.perpwalldist * r.dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_y(int picture_height, int lineheight, int counter)
{
	return (picture_height * ((float)counter / (float)lineheight));
}

int	get_alpha(t_raycast_info *r, t_cubed *cub)
{
	float	color_falloff;

	if (r->perpwalldist / cub->render_distance < 1.0)
		color_falloff = 1 / cos((r->perpwalldist / cub->render_distance)
				* (M_PI / 2));
	else
		color_falloff = 1 / cos(M_PI / 2);
	return ((int)(255 / color_falloff));
}

u_int32_t	get_color(mlx_texture_t *tex, int x, int y, int alpha)
{
	int	red;
	int	green;
	int	blue;
	int	i;

	i = y * tex->width + x;
	red = tex->pixels[i * tex->bytes_per_pixel];
	green = tex->pixels[i * tex->bytes_per_pixel + 1];
	blue = tex->pixels[i * tex->bytes_per_pixel + 2];
	return (get_rgba(red, green, blue, alpha));
}

// function to draw a line of the wall.
// lh = lineHeight. dstart = drawstart. dend = drawend.
// c = counter.
void	draw_wall_segment(uint32_t x, t_raycast_info r,
	t_cubed *cub, mlx_texture_t *text)
{
	t_draw_segment	d;
	int				c;
	int				y;

	c = 0;
	d.lh = (cub->img->width / r.perpwalldist) / cub->fov;
	d.start = (-d.lh / 2) + ((cub->img->height)
			/ 2 + (int)cub->player.head_pitch);
	d.end = (d.lh / 2) + ((cub->img->height) / 2) + (int)cub->player.head_pitch;
	d.wallx = get_wall_x(cub, r);
	d.texx = (double)(text->width * d.wallx);
	y = d.start;
	while (y < d.end && y < (int)cub->img->height)
	{
		if (y >= 0)
		{
			d.texy = get_texture_y(text->height, d.lh, c);
			mlx_put_pixel(cub->img, x, y,
				get_color(text, d.texx, d.texy, get_alpha(&r, cub)));
		}
		c++;
		y++;
	}
}
