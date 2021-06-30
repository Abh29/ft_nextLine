#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*line;
	int				size;
	struct s_list	*next;
}				t_string_list;

int				get_next_line(int fd, char **line);
char			*ft_strdup_(const char *s1);
char			*ft_strchr_(const char *s, int c);
int				ft_strlen_(const char *s);
t_string_list	*ft_lstnew(char *content);
int				ft_string_size(t_string_list *lst);
void			ft_lstclear(t_string_list **lst);
int				ft_lstadd_back(t_string_list **lst, char *line);
int				ft_concat_strings(t_string_list *lst, char **buff);
void			printlist(t_string_list *lst);

#endif