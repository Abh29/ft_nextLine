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
    static int             size;
    int             ret;
    t_string_list   *lst;

    if (line == NULL || fd == -1 || BUFFER_SIZE < 1)
        return (-1);
    if (rest)
    {
        if ((nl = ft_strchr_(rest, '\n')))
        {
            *(nl - 1) = 0;
            *line = ft_strdup_(rest);
            rest = nl;
            if (size == 0)
                return (0);
            return (1);
        }
        ft_lstadd_back(&lst, rest);
        free(rest); // ?!
    }
    buff = malloc(BUFFER_SIZE + 1);
    if (buff == NULL)
        return (-1);
    buff[BUFFER_SIZE] = 0;
    while ((size = read(fd, buff, BUFFER_SIZE)))
    {
        if ((nl = ft_strchr_(buff, '\n')))
        {
            rest = ft_strdup_(nl);
            *(nl - 1) = 0;
            if (ft_lstadd_back(&lst, buff) == -1)
                return (-1);
            break;
        }
        ft_lstadd_back(&lst, buff);
    }
    ret = ft_concat_strings(lst, line);
    if (ret == -1)
        return (-1);
    free(buff);
    ft_lstclear(&lst);
    if (size == 0)
        return (0);
    return (1);
}

int main()
{
    printf("%d",BUFFER_SIZE);
    return 0;
}

