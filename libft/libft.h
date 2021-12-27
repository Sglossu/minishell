/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshawn <bshawn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:16:52 by sglossu           #+#    #+#             */
/*   Updated: 2021/12/17 00:07:40 by bshawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include "stdbool.h"
# include "gnl/get_next_line.h"

typedef struct s_list
{
	char			*val;
	int				flag;
	struct s_list	*next;
}				t_list;

int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strnstr(const char *str1, const char *str2, size_t len);
char		*ft_strrchr(const char *str, int c);
char		*ft_strchr(const char *str, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t l);
size_t		ft_strlcpy(char *dst, const char *src, size_t l);
size_t		ft_strlen(const char *str);
int			ft_memcmp(const void *buf1, const void *buf2, size_t count);
void		*ft_memchr(const void *buf, int c, size_t count);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		**ft_split(char *str, char c);
void		ft_bzero(void *dst, size_t n);
void		*ft_memset(void *dst, int c, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
long long	ft_atoi_long(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strisdigit(char *str);
int			ft_strisalpha(char *str);

t_list		*ft_lstnew(void *val);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstfind(t_list *lst, char *key);
void		ft_lstremove(t_list **lst, t_list *elem);

#endif
