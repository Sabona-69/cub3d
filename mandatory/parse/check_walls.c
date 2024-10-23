#include "../cub3d.h"

void	check_sides(char **map, int x_len, t_data *cub)
{
	int		y;
	int		x;

	y = 1;
	while (map[y])
	{
		x_len = ft_strlen(map[y]) - 1;
		x = skip_char(map[y], ' ');
		if (is_empty(map[y]) == FALSE && (!ft_strchr("1 ", map[y][x_len])
			|| !ft_strchr("1 ", map[y][x_len])))
			exiting(cub, 1);
		y++;
	}
}

void	check_walls(char **map, t_data *cub)
{
	int		y_len;
	int		x_len;
	// int		y = 0;
	int		x;

	x = skip_char(map[0], ' ');
	while (map[0][x])
	{
		if (map[0][x] != '1' && map[0][x] != ' ')
			exiting(cub, 1);
		x++;
	}
	y_len = cub->width - 1;
	x_len = cub->height - 1;
	x = skip_char(map[y_len], ' ');
	while (map[y_len][x])
	{
		if (map[y_len][x] != '1' && map[y_len][x] != ' ')
			exiting(cub, 1);
		x++;
	}
	check_sides(map, x_len, cub);
}
