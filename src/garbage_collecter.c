#include "../cube3d.h"

void	*gc_malloc(t_garbage_collector **gc, size_t size)
{
	void				*ptr;
	t_garbage_collector	*new_node;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_collector));
	if (new_node == NULL)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = *gc;
	*gc = new_node;
	return (ptr);
}

void	gc_free(t_garbage_collector **gc)
{
	t_garbage_collector *current;
	t_garbage_collector *next;

	current = *gc;
	while (current != NULL)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*gc = NULL;
}