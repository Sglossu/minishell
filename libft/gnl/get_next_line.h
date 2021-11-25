/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglossu <sglossu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:12:52 by sglossu           #+#    #+#             */
/*   Updated: 2021/08/19 18:19:27 by sglossu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup_gnl(const char *str, char c);
char	*ft_strdup_next(const char *str);
char	*ft_strjoin_gnl(char *s1, char const *s2);
size_t	ft_strlen_gnl(const char *str);
char	*transposition(char *buf, char *static_buf, char **line);

#endif
