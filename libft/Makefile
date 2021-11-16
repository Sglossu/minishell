NAME = libft.a

SRC_NAME	=	ft_strlen.c				ft_strnstr.c				ft_strncmp.c\
				ft_atoi.c				ft_isalnum.c				ft_isascii.c\
				ft_isalpha.c			ft_isdigit.c				ft_isprint.c\
				ft_memcmp.c				ft_strchr.c					ft_strlcat.c\
				ft_strlcpy.c			ft_strrchr.c\
				ft_tolower.c			ft_toupper.c				ft_memchr.c\
				ft_memmove.c			ft_memccpy.c				ft_memcpy.c\
				ft_split.c				ft_bzero.c					ft_memset.c\
				ft_calloc.c				ft_strdup.c					ft_substr.c\
				ft_strjoin.c			ft_strtrim.c				ft_putstr_fd.c\
				ft_putchar_fd.c			ft_putnbr_fd.c				ft_putendl_fd.c\
				ft_itoa.c				ft_strmapi.c				ft_atoi_long.c \
				gnl/get_next_line.c		gnl/get_next_line_utils.c	ft_strcmp.c

OBJS = $(SRC_NAME:.c=.o)

HEAD = libft.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o:%.c ${HEAD}
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME)

re : fclean all

.PHONY: clean fclean all re