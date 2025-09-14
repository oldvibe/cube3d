#include "../cube3d.h"
#include <fcntl.h>
#include <unistd.h>

void	init_game(t_data *data)
{
    data->mlx = mlx_init();
    if (data->mlx == NULL)
    {
        write(2, "Error\nFailed to initialize MLX\n", 32);
        exit(1);
    }
    data->win = mlx_new_window(data->mlx, 800, 600, "Cub3D");
    if (data->win == NULL)
    {
        write(2, "Error\nFailed to create window\n", 30);
        free(data->mlx);
        exit(1);
    }
    data->gc = NULL;
}

int	load_map(const char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		height = 0, width;
	int		len;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0, width = 0;
	while ((line = get_next_line(fd, &data->gc)))
	{
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > width)
			width = len;
		height++;
		free(line);
	}
	close(fd);
	data->map_width = width;
	data->map_height = height;
	data->map = gc_malloc(&data->gc, height * sizeof(char *));
	if (!data->map)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	while ((line = get_next_line(fd, &data->gc)) && i < height)
	{
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		data->map[i] = gc_malloc(&data->gc, (width + 1) * sizeof(char));
		if (!data->map[i])
			return (-1);
		memset(data->map[i], '0', width);
		strncpy(data->map[i], line, len);
		data->map[i][width] = '\0';
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		if (!data->map[i])
			return (-1);
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] != '0' && data->map[i][j] != '1')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_map(t_data *data)
{
	gc_free(&data->gc);
	data->map = NULL;
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
		free(data->mlx);
}