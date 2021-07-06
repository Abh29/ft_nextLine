#include "get_next_line.h"

char	*ft_strchr_(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_(const char *s1)
{
	char	*out;
	size_t	size;
	char	*save;

	size = ft_strlen_(s1);
	out = (char *)malloc(size + 1);
	if (out == NULL)
		return (NULL);
	save = out;
	while (*s1)
		*out++ = *s1++;
	*out = 0;
	return (save);
}

static int	ft_first_part(char **rest, char **line, t_string_list **lst)
{
	char	*nl;

	if (*rest && ft_strlen_(*rest) > 0)
	{
		nl = ft_strchr_(*rest, '\n');
		if (nl)
		{
			*nl = 0;
			*line = ft_strdup_(*rest);
			nl = ft_strdup_(nl + 1);
			free(*rest);
			*rest = ft_strdup_(nl);
			free(nl);
			return (1);
		}
		ft_lstadd_back(lst, *rest);
		free(nl);
		nl = NULL;
		free(*rest);
		*rest = NULL;
	}
	return (2);
}

static int	ft_second_part(int	fd, int *size, \
						char **rest, t_string_list **lst)
{
	char	*buff;
	char	*nl;

	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (-1);
	*size = read(fd, buff, BUFFER_SIZE);
	while (*size > 0)
	{
		buff[*size] = 0;
		nl = ft_strchr_(buff, '\n');
		if (nl)
		{
			if (*(nl + 1))
				*rest = ft_strdup_(nl + 1);
			*nl = 0;
			if (ft_lstadd_back(lst, buff) == -1)
				return (-1);
			break ;
		}
		ft_lstadd_back(lst, buff);
		*size = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static char		*rest;
	static int		size;
	t_string_list	*lst;

	lst = NULL;
	if (line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (ft_first_part(&rest, line, &lst) == 1)
		return (1);
	if (ft_second_part(fd, &size, &rest, &lst) == -1 || \
		ft_concat_strings(lst, line) == -1)
		return (-1);
	ft_lstclear(&lst, free);
	if (size == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (size == 0)
	{
		free(rest);
		return (0);
	}
	return (1);
}
