/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesbess <tbesbess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:10:45 by tbesbess          #+#    #+#             */
/*   Updated: 2024/10/18 10:10:45 by tbesbess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < 0)
		return ;
	else if (x >= img->width)
		return ;
	if (y < 0)
		return ;
	else if (y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void set_player(t_game *game)
{
	char c;

    game->player = malloc(sizeof(t_pl));
	game->rays = malloc(sizeof(t_ray));
    c = game->data->map[game->data->player_postion.y][game->data->player_postion.x];
    if (c == 'E')
        game->player->direction = 0;
    else if (c == 'N')
        game->player->direction = (3 * M_PI) / 2;
    else if (c == 'W')
        game->player->direction = M_PI;
    else if (c == 'S')
        game->player->direction = M_PI / 2;
    game->player->star.x = (game->data->player_postion.x * TILE_SIZE) + TILE_SIZE / 2;
    game->player->star.y = (game->data->player_postion.y * TILE_SIZE) + TILE_SIZE / 2;
    game->player->view = VIEW * (M_PI / 180);
    game->player->walk = STOP;
    game->player->turn = STOP;
}

void handle_key(mlx_key_data_t keydata, void *param){
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
		exit(0);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->walk = LEFT;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->walk = RIGHT;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->walk = DOWN;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player->walk = UP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_LEFT;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player->turn = TURN_RIGHT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->player->walk = STOP;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player->turn = STOP;
}

void load_textures(t_game *game)
{
	game->tx = malloc(sizeof(t_tx));

	// if (!)
	game->tx->e = mlx_load_png(game->data->EA);
	game->tx->w = mlx_load_png(game->data->WE);
	game->tx->s = mlx_load_png(game->data->SO);
	game->tx->n = mlx_load_png(game->data->NO);
}



double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

static void	turn(t_game *game, int flag)
{
	if (flag == 1)
	{
		game->player->direction += ROTATION_SPEED;
		game->player->direction = normalize_angle(game->player->direction);
	}
	if (flag == 2)
	{
		game->player->direction -= ROTATION_SPEED;
		game->player->direction = normalize_angle(game->player->direction);
	}
}


int	is_wall(double x, double y, t_game *game)
{
	t_pos	m;

	if (x < 0 || y < 0)
		return (1);
	m.x = floor(x / TILE_SIZE);
	m.y = floor(y / TILE_SIZE);
	if (m.y < 0 || m.y >= game->data->width
		|| m.x < 0 || m.x >= game->data->height)
		return (1);
	if (game->data->map[m.y][m.x] == '1')
		return (1);
	return (0);
}

static int	check_collision(t_game *game, int x, int y)
{
	return (is_wall(x - COLLISION, y - COLLISION, game)
		|| is_wall(x + COLLISION, y - COLLISION, game)
		|| is_wall(x - COLLISION, y + COLLISION, game)
		|| is_wall(x + COLLISION, y + COLLISION, game));
}

void	walk_player(t_game *game, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = round(game->player->star.x + move_x);
	new_y = round(game->player->star.y + move_y);
	if (!check_collision(game, new_x, game->player->star.y))
		game->player->star.x = new_x;
	if (!check_collision(game, game->player->star.x, new_y))
		game->player->star.y = new_y;
}

void	movement(t_game *game, double move_x, double move_y)
{
	if (game->player->turn == TURN_RIGHT)
		turn(game, 1);
	else if (game->player->turn == TURN_LEFT)
		turn(game, 2);
	if (game->player->walk == RIGHT)
	{
		move_x = -sin(game->player->direction) * MOVE_SPEED;
		move_y = cos(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == LEFT)
	{
		move_x = sin(game->player->direction) * MOVE_SPEED;
		move_y = -cos(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == DOWN)
	{
		move_x = -cos(game->player->direction) * MOVE_SPEED;
		move_y = -sin(game->player->direction) * MOVE_SPEED;
	}
	else if (game->player->walk == UP)
	{
		move_x = cos(game->player->direction) * MOVE_SPEED;
		move_y = sin(game->player->direction) * MOVE_SPEED;
	}
	walk_player(game, move_x, move_y);
}



void	adjust_step(t_game *game, t_pos_d *delta, int is_vertical)
{
	if (is_vertical)
	{
		if (game->rays->left)
			delta->x *= -1;
		if (game->rays->up && delta->y > 0)
			delta->y *= -1;
		if (game->rays->down && delta->y < 0)
			delta->y *= -1;
	}
	else
	{
		if (game->rays->up)
			delta->y *= -1;
		if (game->rays->left && delta->x > 0)
			delta->x *= -1;
		if (game->rays->right && delta->x < 0)
			delta->x *= -1;
	}
}

double	calcul_distance(t_pos_d start, t_pos_d end)
{
	return (sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2)));
}

static double	horizontal_intersect(t_game *game)
{
	t_pos_d	inter;
	t_pos_d	delta;

	inter.y = floor(game->player->star.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays->down)
		inter.y += TILE_SIZE;
	inter.x = game->player->star.x
		+ (inter.y - game->player->star.y) / tan(game->rays->angl);
	delta.y = TILE_SIZE;
	delta.x = TILE_SIZE / tan(game->rays->angl);
	adjust_step(game, &delta, 0);
	while (!is_wall(inter.x, inter.y - game->rays->up, game))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	game->rays->h_wall.x = inter.x;
	game->rays->h_wall.y = inter.y;
	return (calcul_distance(inter, game->player->star));
}

static double	vertical_intersect(t_game *game)
{
	t_pos_d	inter;
	t_pos_d	delta;

	inter.x = floor(game->player->star.x / TILE_SIZE) * TILE_SIZE;
	if (game->rays->right)
		inter.x += TILE_SIZE;
	inter.y = game->player->star.y
		+ (inter.x - game->player->star.x) * tan(game->rays->angl);
	delta.x = TILE_SIZE;
	delta.y = TILE_SIZE * tan(game->rays->angl);
	adjust_step(game, &delta, 1);
	while (!is_wall(inter.x - game->rays->left, inter.y, game))
	{
		inter.x += delta.x;
		inter.y += delta.y;
	}
	game->rays->v_wall.x = inter.x;
	game->rays->v_wall.y = inter.y;
	return (calcul_distance(inter, game->player->star));
}

uint32_t	ft_get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

static void	draw_ceiling(t_game *game, int wall_t)
{
	int		i;
	int		color;

	color = ft_get_color(game->data->C[0], game->data->C[1],game->data->C[2], 255);
	i = 0;
	while (i < wall_t)
		my_pixel_put(game->img, game->rays->index, i++, color);
}

mlx_texture_t	*get_texture(t_game *game)
{
	if (game->rays->was_hit_vertical)
	{
		if (game->rays->angl > M_PI / 2 && game->rays->angl < 3 * (M_PI / 2))
			return (game->tx->e);
		else
			return (game->tx->w);
	}
	else
	{
		if (game->rays->angl > 0 && game->rays->angl < M_PI)
			return (game->tx->n);
		else
			return (game->tx->s);
	}
}

int	get_texture_x(mlx_texture_t *texture, t_game *game)
{
	double	offset_x;

	if (game->rays->was_hit_vertical)
		offset_x = fmod(game->rays->v_wall.y, TILE_SIZE);
	else
		offset_x = fmod(game->rays->h_wall.x, TILE_SIZE);
	offset_x = (offset_x * texture->width) / TILE_SIZE;
	return (offset_x);
}

int	get_texture_y(mlx_texture_t *texture, t_game *game, int y, int wall_h)
{
	double	step;
	double	offset_y;
	int		wall_t;

	wall_t = (game->win->height / 2) - (wall_h / 2);
	step = (double)texture->height / wall_h;
	offset_y = ((y - wall_t) * step);
	if (offset_y >= texture->height)
		offset_y = texture->height - 1;
	if (offset_y < 0)
		offset_y = 0;
	return (offset_y);
}

uint32_t	reverse_bytes(uint32_t c)
{
	uint32_t	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}



static void	draw_wall(t_game *game, int wall_t, int wall_b, double wall_h)
{
	t_pos		offset;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	uint32_t		color;
	int				y;

	texture = get_texture(game);
	arr = (uint32_t *)texture->pixels;
	offset.x = get_texture_x(texture, game);
	if (game->tx->w == texture || game->tx->s == texture)
		offset.x = texture->width - offset.x - 1;
	y = wall_t;
	while (y < wall_b)
	{
		offset.y = get_texture_y(texture, game, y, wall_h);
		color = reverse_bytes(arr[offset.y * texture->width + offset.x]);
		my_pixel_put(game->img, game->rays->index, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int wall_b)
{
	int		color;
	color = ft_get_color(game->data->F[0], game->data->F[1], game->data->F[2], 255);
	while (wall_b < game->win->height)
		my_pixel_put(game->img, game->rays->index, wall_b++, color);
}

void	projected_wall(t_game *game)
{
	double	wall_h;
	double	disproplan;
	int		wall_t;
	int		wall_b;

	game->rays->distance *= cos(game->rays->angl - game->player->direction);
	disproplan = (game->win->width / 2) / tan(game->player->view / 2);
	wall_h = (TILE_SIZE / game->rays->distance) * disproplan;
	wall_b = (game->win->height / 2) + (wall_h / 2);
	wall_t = (game->win->height / 2) - (wall_h / 2);
	if (wall_b > game->win->height)
		wall_b = game->win->height;
	if (wall_t < 0)
		wall_t = 0;
	draw_ceiling(game, wall_t);
	draw_wall(game, wall_t, wall_b, wall_h);
	draw_floor(game, wall_b);
}

void	check_rayfacing(t_game *game, double angle)
{
	game->rays->down = angle > 0 && angle < M_PI;
	game->rays->up = !game->rays->down;
	game->rays->right = angle < (M_PI / 2) || angle > (3 * M_PI / 2);
	game->rays->left = !game->rays->right;
}

void raycasting(t_game *game)
{
	t_pos_d	distance;

	game->rays->index = 0;
	game->rays->angl = game->player->direction - (game->player->view / 2);
	while (game->rays->index < game->win->width)
	{
		game->rays->angl = normalize_angle(game->rays->angl);
		check_rayfacing(game, game->rays->angl);
		distance.x = horizontal_intersect(game);
		distance.y = vertical_intersect(game);
		if (distance.y <= distance.x)
		{
			game->rays->distance = distance.y;
			game->rays->was_hit_vertical = 1;
		}
		else
		{
			game->rays->distance = distance.x;
			game->rays->was_hit_vertical = 0;
		}
		projected_wall(game);
		game->rays->index++;
		game->rays->angl += (game->player->view / game->win->width);
	}
}

void	ft_clear_img(mlx_image_t *img)
{
	u_int32_t	i;
	u_int16_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
}

void update(void *param)
{
	t_game *game = param;
	ft_clear_img(game->img);
	mlx_resize_image(game->img, game->win->width, game->win->height);
	movement(game, 0, 0);
	raycasting(game);
}
void create_game(t_game *game)
{
    int32_t window_w;
    int32_t window_h;

    game->win = mlx_init(WIDTH, HEIGHT, "cub3D", false);
    window_w = game->win->width ;
    window_h = game->win->height;
    game->img = mlx_new_image(game->win, window_w, window_h);
	load_textures(game);
	mlx_image_to_window(game->win, game->img, 0, 0);
    set_player(game);
	mlx_loop_hook(game->win, &update, game);
	mlx_key_hook(game->win, &handle_key, game);
    mlx_loop(game->win);
}

int main(int ac, char **av)
{
	t_data  *cub;
    t_game  *game;


	if (ac != 2 || ft_strlen(av[1]) < 4 || ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		return (printf("Please Insert \"./cub\" + valid map\n"), 1);
	cub = malloc(sizeof(t_data));
	if (!cub)
		return (ft_putstr_fd("malloc failed ", 2), 1);
	ft_memset(cub, 0, sizeof(t_data));
	parse_it(av[1], cub);
    game = malloc(sizeof(t_game));
	ft_memset(game, 0, sizeof(t_game));
    game->data = cub;
	create_game(game);
	exiting(cub, 0);
}