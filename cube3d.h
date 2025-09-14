#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <stdlib.h>
# include <unistd.h>

#define BUFFER_SIZE 32

typedef struct s_garbage_collector
{
    void						*ptr;
    struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_data
{
    void						*mlx;
    void						*win;
    char						**map;
    int							map_width;
    int							map_height;
    int							tile_size;
    double						player_x;
    double						player_y;
    double						player_angle;
    double						fov;
    t_garbage_collector			*gc;
}								t_data;

void	init_game(t_data *data);
int		render_game(t_data *data);
void	free_map(t_data *data);
void	*gc_malloc(t_garbage_collector **gc, size_t size);
void	gc_free(t_garbage_collector **gc);
char	*get_next_line(int fd, t_garbage_collector **gc);
char    *ft_strdup(t_garbage_collector **gc, const char *s1);
char    *ft_substr(t_garbage_collector **gc, char const *s, unsigned int start, size_t len);
size_t  ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
char    *ft_strjoin_gc(t_garbage_collector **gc, char const *s1, char const *s2);
int		load_map(const char *filename, t_data *data);

#endif