#include "../cube3d.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int	handle_key(int keycode, t_data *data)
{
    int new_x = (int)data->player_x;
    int new_y = (int)data->player_y;

    if (keycode == 65307) 
	free_map(data), exit(0);
    if (keycode == 'w' || keycode == 119)
	new_y -= 1;
    if (keycode == 's' || keycode == 115)
	new_y += 1;
    if (keycode == 'a' || keycode == 97)
	new_x -= 1;
    if (keycode == 'd' || keycode == 100)
	new_x += 1;

    // Clamp to map and avoid walls
    if (new_x >= 0 && new_x < data->map_width &&
        new_y >= 0 && new_y < data->map_height &&
        data->map[new_y][new_x] == '0')
    {
        data->player_x = new_x;
        data->player_y = new_y;
    }
    return (0);
}

int	main(void)
{
	t_data data;
	
	init_game(&data);
	extern char *test_map[];
	data.map = test_map;
	data.map_width = 6;
	data.map_height = 6;
	data.tile_size = WIN_WIDTH / data.map_width; // scale to window width
	data.player_x = 2;
	data.player_y = 2;

	mlx_loop_hook(data.mlx, render_game, &data);
	mlx_key_hook(data.win, handle_key, &data);

	mlx_loop(data.mlx);

	free_map(&data);
	return (0);
}