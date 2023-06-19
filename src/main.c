#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_map	map;
	if (argc != 2)
	{
		printf("Error invalid arguments: Usage: ./cub3d + ANOTHER ARGUMENT stoopid..\n");
		return (EXIT_FAILURE);
	}
	if (!parser(argv[1], &map))
	{
		printf("Error something went wrong int the parser woopsies\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}