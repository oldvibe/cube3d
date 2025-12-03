#include "../cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * 0.05;
	new_y = game->player.pos_y + game->player.dir_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * 0.05;
	new_y = game->player.pos_y - game->player.dir_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * 0.05;
	new_y = game->player.pos_y - game->player.plane_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * 0.05;
	new_y = game->player.pos_y + game->player.plane_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

int	game_loop(t_game *game)
{
	int	updated;

	updated = 0;
	if (game->key_w)
	{
		move_forward(game);
		updated = 1;
	}
	if (game->key_s)
	{
		move_backward(game);
		updated = 1;
	}
	if (game->key_a)
	{
		move_left(game);
		updated = 1;
	}
	if (game->key_d)
	{
		move_right(game);
		updated = 1;
	}
	if (game->key_left)
	{
		rotate_left(game);
		updated = 1;
	}
	if (game->key_right)
	{
		rotate_right(game);
		updated = 1;
	}
	if (updated)
		raycasting(game);
	return (0);
}
