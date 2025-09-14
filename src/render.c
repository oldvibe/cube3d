#include "../cube3d.h"

int	render_game(t_data *data)
{
    int i;
    int j;
    int color;
    int y;
    int x;
    int dy;
    int dx;

    mlx_clear_window(data->mlx, data->win);

    i = 0;
    while (i < data->map_height && data->map)
    {
        if (data->map[i] == NULL)
        {
            i++;
            continue;
        }
        j = 0;
        while (j < data->map_width)
        {
            if (data->map[i][j] == '1')
                color = 0x0000FF;
            else
                color = 0x000000;
            y = i * data->tile_size;
            x = j * data->tile_size;
            dy = 0;
            while (dy < data->tile_size)
            {
                dx = 0;
                while (dx < data->tile_size)
                {
                    mlx_pixel_put(data->mlx, data->win, x + dx, y + dy, color);
                    dx++;
                }
                dy++;
            }
            j++;
        }
        i++;
    }

    // Draw player
    int player_size = 10;
    int px = (int)(data->player_x * data->tile_size + data->tile_size / 2);
    int py = (int)(data->player_y * data->tile_size + data->tile_size / 2);
    dy = -player_size / 2;
    while (dy < player_size / 2)
    {
        dx = -player_size / 2;
        while (dx < player_size / 2)
        {
            mlx_pixel_put(data->mlx, data->win, px + dx, py + dy, 0xFF0000);
            dx++;
        }
        dy++;
    }
    return (0);
}
