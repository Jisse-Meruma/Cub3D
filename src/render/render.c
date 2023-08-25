#include <cub3d.h>

t_vec	get_dir(uint32_t x, t_cubed *cub)
{
	double	camx;
	t_vec	raydir;

	camx = cub->fov * ((float)x / cub->img->width) - (cub->fov / 2);
	raydir.x = cub->player.dir.x + (cub->player.c_plane.x) * camx;
	raydir.y = cub->player.dir.y + (cub->player.c_plane.y) * camx;
	return (raydir);
}

void	draw_with_raycasts(t_cubed *cub)
{
	uint32_t		x;
	t_raycast_info	r;
	t_vec			dir;
	t_vec			pos;

	x = 0;
	pos = cub->player.pos;
	while (x < cub->img->width)
	{
		dir = get_dir(x, cub);
		r = raycast(pos, dir, cub->map);
		draw_wall_segment(x, r, cub,
			get_texture(&r, &cub->map.elements.texture));
		draw_minimap(r, cub);
		x++;
	}
}

void	clear_images(t_cubed *cub)
{
	ft_bzero(cub->img->pixels, (cub->img->width * cub->img->height) * 4);
	ft_bzero(cub->minimap->pixels,
		sizeof(uint32_t) * cub->minimap->width * cub->minimap->height);
	ft_bzero(cub->minimap_view->pixels,
		sizeof(uint32_t) * cub->minimap->width * cub->minimap->height);
}

void	render_frame(t_cubed *cub)
{
	clear_images(cub);
	draw_floor_and_ceiling(cub);
	draw_with_raycasts(cub);
	draw_minimap_player(cub);
}
