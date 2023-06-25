#include "struct.h"
#include <cub3d.h>

int main(int argc, char *argv[])
{
	t_cubed	cub;	

	if (argc != 2)
	{
		printf("Error invalid arguments: Usage: ./cub3d + ANOTHER ARGUMENT stoopid..\n");
		return (EXIT_FAILURE);
	}
	if (!parser(argv[1], &cub.map))
	{
		printf("Error something went wrong int the parser woopsies\n");
		return (EXIT_FAILURE);
	}
	if (!cub_init(&cub))
		return (false);
	if (!cub_loop(&cub))
		return (false);
	return (EXIT_SUCCESS);
}
