NAME		=	minishell
DIR			=	./srcs/
DIR_HEAD	=	./includes/
DIR_BUILD	=	./buildins/
DIR_UTILS	=	./utils/
DIR_SRCS	=	./srcs/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	main.c \
				\
				$(DIR_BUILD)ft_pwd.c			$(DIR_BUILD)ft_cd.c				$(DIR_BUILD)ft_echo.c \
				$(DIR_BUILD)ft_env.c			$(DIR_BUILD)ft_unset.c			$(DIR_BUILD)ft_export.c \
				$(DIR_BUILD)ft_exit.c \
				\
				$(DIR_UTILS)ft_sort_params.c	$(DIR_UTILS)about_memory.c		$(DIR_UTILS)find.c\
				\
				$(DIR_SRCS)init.c				$(DIR_SRCS)main_work.c

OBJS		=	$(SRCS:.c=.o)

HEAD		=	$(DIR_HEAD)minishell.h

LIB			=	libft/libft.a
BLIB		=	./libft/libft.a

.c.o:
		$(CC) $(CFLAGS) -c  -I$(DIR_HEAD) $< -o $(<:.c=.o)

.PHONY		:	all clean fclean re bonus
all			:	$(NAME)

$(OBJS)		:	$(HEAD)

$(NAME)		:	$(OBJS)
		$(MAKE) -C libft
		$(CC) -g $(CFLAGS) -Llibft -lft -I$(DIR_HEAD) $(SRCS) -o $(NAME)

clean		:
		$(MAKE) clean -C libft
		$(RM) $(OBJS)

fclean		:	clean
		$(MAKE) fclean -C libft
		$(RM) $(NAME)

re			:	fclean all
