#include "../cube3d.h"

static char	*getlinex(t_garbage_collector **gc, char **storage)
{
    char	*line;
    char	*newline_pos;
    char	*temp;

    newline_pos = ft_strchr(*storage, '\n');
    if (newline_pos)
    {
        line = ft_substr(gc, *storage, 0, newline_pos - *storage + 1);
        temp = ft_strdup(gc, newline_pos + 1);
        *storage = temp;
    }
    else
    {
        line = ft_strdup(gc, *storage);
        *storage = NULL;
    }
    return (line);
}

char	*free_and_join(t_garbage_collector **gc, char *str, char *buffer)
{
    char	*temp;

    temp = ft_strjoin_gc(gc, str, buffer);
    // Do NOT free(str); GC will handle it
    return (temp);
}

static char	*read_and_store(t_garbage_collector **gc, int fd, char *storage)
{
    char	*buffer;
    int		length_read;

    if (BUFFER_SIZE <= 0)
        return (NULL);
    buffer = gc_malloc(gc, BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (!ft_strchr(storage, '\n'))
    {
        length_read = read(fd, buffer, BUFFER_SIZE);
        if (length_read < 0)
            return (NULL); // Do NOT free(storage) or buffer
        if (length_read == 0)
            break ;
        buffer[length_read] = '\0';
        if (!storage)
           storage = ft_strdup(gc, buffer);
        else
            storage = free_and_join(gc, storage, buffer);
    }
    // Do NOT free(buffer); GC will handle it
    return (storage);
}

char	*get_next_line(int fd, t_garbage_collector **gc)
{
    static char	*storage = NULL;
    char		*line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    storage = read_and_store(gc, fd, storage);
    if (!storage)
        return (NULL);
    if (!*storage)
    {
        storage = NULL;
        return (NULL);
    }
    line = getlinex(gc, &storage);
    if (!storage || !*storage)
        storage = NULL;
    return (line);
}
