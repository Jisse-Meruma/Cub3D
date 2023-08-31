/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 12:21:56 by dritsema      #+#    #+#                 */
/*   Updated: 2023/08/31 14:01:36 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <cub3d.h>
#include <stdlib.h>

void	error_exit(const char *str, t_cubed *cub)
{
	(void)cub;
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	cub_end(cub);
}

int	main(int argc, char *argv[])
{
	t_cubed	cub;

	ft_bzero(&cub, sizeof(t_cubed));
	if (argc != 2)
		return (error_exit("Invalid amount of arguments [2]\n",
				&cub), EXIT_FAILURE);
	if (!parser(argv[1], &cub))
		return (EXIT_FAILURE);
	if (!cub_init(&cub))
		return (false);
	if (!cub_loop(&cub))
		return (false);
	cub_end(&cub);
	return (EXIT_SUCCESS);
}
