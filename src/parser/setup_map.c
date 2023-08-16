#include "struct.h"
#include <cub3d.h>
#include <stdbool.h>

bool	allocate_map_tiles(t_map *map)
{
	int	i;

	i = 0;
	map->map = ft_calloc(map->height + 1, sizeof(t_tile *));
	if (map->map == NULL)
		return (false);
	while (i < map->height)
	{
		map->map[i] = ft_calloc(map->width + 1, sizeof(t_tile));
		if ((map->map)[i] == NULL)
		{
			ft_2dfree((char **)map->map);
			return (false);
		}
		i++;
	}
	return (true);
}

t_tile	get_tile(char c)
{
	if (c == ' ')
		return (SPACE);
	else if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (PNORTH);
	else if (c == 'E')
		return (PEAST);
	else if (c == 'S')
		return (PSOUTH);
	else if (c == 'W')
		return (PWEST);
	return (SPACE);
}

bool	get_player_pos(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == PNORTH || map->map[y][x] == PEAST
					|| map->map[y][x] == PSOUTH || map->map[y][x] == PWEST)
			{
				if (map->px != -1)
					return (false);
				map->py = y;
				map->px = x;
			}
			x++;
		}
		y++;
	}
	return (true);
}

void	set_map_tiles(t_map *map)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = map_start_index(map->str_map);
	while (map->str_map[i] && valid_map_str(map->str_map[i]))
	{
		j = 0;
		while (map->str_map[i][j])
		{
			map->map[y][j] = get_tile(map->str_map[i][j]);
			j++;
		}
		y++;
		i++;
	}
}

bool	setup_map(t_cubed *cub)
{
	cub->map.px = -1;
	cub->map.py = -1;
	if (!determine_map_height(&cub->map))
		return (error_exit("Failed to determine map height\n", cub), false);
	if (!determine_map_width(&cub->map))
		return (error_exit("Failed to determine map width\n", cub), false);
	if (!allocate_map_tiles(&cub->map))
		return (error_exit("Map tile allocation failed\n", cub), false);
	set_map_tiles(&cub->map);
	if (!get_player_pos(&cub->map))
		return (error_exit("mulitple player positions\n", cub), false);
	return (true);
}
