#include "cub3d.h"

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		(1) && (s1++, s2++);
	return (*s1 - *s2);
}

void    store_map(char *s, t_data *cub)
{
	int		fd;
	char	*line;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return(printf("Invalid map file !\n"), exit(1));
	line = get_next_line(fd);
	while(line)
	{

	}
}


void    store_instructions(char *s, t_data *cub)
{
	int		fd;
	char	*line;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return(printf("Invalid map file !\n"), exit(1));
	line = get_next_line(fd);
	while(line)
	{
		if (strncmp("R ", line, 2) == 0)
			cub->R = strdup(line + 2);
		else if (strncmp("NO ", line, 3) == 0)
			cub->NO = strdup(line + 3);
		else if (strncmp("SO ", line, 3) == 0)
			cub->SO = strdup(line + 3);
		else if (strncmp("WE ", line, 3) == 0)
			cub->WE = strdup(line + 3);
		else if (strncmp("EA ", line, 3) == 0)
			cub->EA = strdup(line + 3);
		else if (strncmp("S ", line, 2) == 0)
			cub->S = strdup(line + 2);
		else if (strncmp("F ", line, 2) == 0)
			cub->F = strdup(line + 2);
		else if (strncmp("C ", line, 2) == 0)
			cub->C = strdup(line + 2);
		else
			
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!cub->R)
		return(printf("Please set resolution !\n"), exit(1));
	else if (!cub->C)
		return(printf("Please set ceilling color !\n"), exit(1));
	else if (!cub->F)
		return(printf("Please set the floor colore !\n"), exit(1));
	else if (!cub->S)
		return(printf("Please set the sprite texture !\n"), exit(1));
	else if (!cub->EA)
		return(printf("Please set the east texture !\n"), exit(1));
	else if (!cub->NO)
		return(printf("Please set the north texture !\n"), exit(1));
	else if (!cub->SO)
		return(printf("Please set  the south texture !\n"), exit(1));
	else if (!cub->WE)
		return(printf("Please set  the west texture !\n"), exit(1));
}

int main(int ac, char **av)
{
	t_data	*cub;

	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return(printf("Please Insert name of the program + a valid map\n"), 1);
	memset(cub, 0, sizeof(t_data));
	store_instructions(av[1], cub);
	// store_map(av[1], cub);
}