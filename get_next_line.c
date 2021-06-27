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
    char    *save;

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

int get_next_line(int fd, char **line)
{
    static char     *rest;
    char            *buff;
    char            *nl;
    static int      size;
    int             ret;
    t_string_list   *lst;

    lst = NULL;
    //ft_lstadd_back(&lst, "");
    if (line == NULL || fd == -1 || BUFFER_SIZE < 1)
        return (-1);
    if (rest && ft_strlen_(rest) > 0)
    {
        if ((nl = ft_strchr_(rest, '\n')))
        {
            *nl = 0;
            *line = ft_strdup_(rest);
            nl = ft_strdup_(nl + 1);
            free(rest);
            rest = nl;
            return (1);
        }
        ft_lstadd_back(&lst, rest);
        if (rest)
            free(rest);
    }
    buff = malloc(BUFFER_SIZE + 1);
    if (buff == NULL)
        return (-1);
    buff[BUFFER_SIZE] = 0;
    while ((size = read(fd, buff, BUFFER_SIZE)))
    {
        buff[size] = 0;
        if ((nl = ft_strchr_(buff, '\n')))
        {
            if (*(nl + 1))
                rest = ft_strdup_(nl + 1);
            *nl = 0;
            if (ft_lstadd_back(&lst, buff) == -1)
                return (-1);
            break;
        }
        ft_lstadd_back(&lst, buff);
    }
    free(buff);
    ret = ft_concat_strings(lst, line);
    if (ret == -1)
        return (-1);
    ft_lstclear(&lst);
    free(lst);
    if (size == 0)
        return (0);
    return (1);
}
