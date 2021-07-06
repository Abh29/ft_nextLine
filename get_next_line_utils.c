#include "get_next_line.h"

int	ft_strlen_(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_string_size(t_string_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size += lst->size;
		lst = lst->next;
	}
	return (size);
}

void	ft_lstclear(t_string_list **lst, void (*del)(void*))
{
	t_string_list	*p;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		del(p->line);
		free(p);
	}
	free(*lst);
}

int	ft_lstadd_back(t_string_list **lst, char *line)
{
	t_string_list	*save;
	t_string_list	*new;

	new = malloc(sizeof(t_string_list));
	if (new == NULL)
		return (-1);
	new->size = ft_strlen_(line);
	new->line = ft_strdup_(line);
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return (1);
	}
	save = *lst;
	while (save->next)
		save = save->next;
	save->next = new;
	return (1);
}

int	ft_concat_strings(t_string_list *lst, char **buff)
{
	int	i;
	int	j;

	if (buff == NULL)
		return (-1);
	if (lst == NULL)
	{
		*buff = malloc(1);
		**buff = 0;
		return (0);
	}
	*buff = malloc(ft_string_size(lst) + 1);
	if (*buff == NULL)
		return (-1);
	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->line[j])
			(*buff)[i++] = lst->line[j++];
		lst = lst->next;
	}
	(*buff)[i] = 0;
	return (i);
}
