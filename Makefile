NAME		=	minishell
DIR			=	./srcs/
DIR_HEAD	=	./includes/
DIR_BUILD	=	./buildins/
DIR_UTILS	=	./utils/
DIR_SRCS	=	./srcs/
DIR_PIPE	=	./pipe/
DIR_PARSE	=	./parse/
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
				$(DIR_UTILS)free.c \
				\
				$(DIR_SRCS)init.c				$(DIR_SRCS)main_work.c			$(DIR_SRCS)command_exist.c \
				$(DIR_SRCS)one_direct.c \
				\
				$(DIR_PIPE)pipe_main.c			$(DIR_PIPE)functions_for_direct.c \
				\
				$(DIR_PARSE)parser.c			$(DIR_PARSE)parser_utils.c		$(DIR_PARSE)lists.c \
				$(DIR_PARSE)cmd_parse.c\
				\

OBJS		=	$(SRCS:.c=.o)

HEAD		=	$(DIR_HEAD)minishell.h

LIB			=	libft/libft.a
BLIB		=	./libft/libft.a

RDL			= -lreadline
RDL_MAC		= -lreadline -L/usr/local/opt/readline/lib
RDL_MAC_C	= -I/usr/local/opt/readline/include

.c.o:
		$(CC) $(CFLAGS) -c -I$(DIR_HEAD) $(RDL_MAC_C) $< -o $(<:.c=.o)

.PHONY		:	all clean fclean re bonus
all			:	$(NAME)

$(OBJS)		:	$(HEAD)

$(NAME)		:	$(OBJS)
		$(MAKE) -C libft
		$(CC) -g $(CFLAGS) -Llibft -lft -I$(DIR_HEAD) $(OBJS) $(BLIB)  -o $(NAME) $(RDL_MAC)

clean		:
		$(MAKE) clean -C libft
		$(RM) $(OBJS)

fclean		:	clean
		$(MAKE) fclean -C libft
		$(RM) $(NAME)

re			:	fclean all
